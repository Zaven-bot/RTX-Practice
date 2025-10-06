#include <iostream>
#include <thread>
#include <boost/optional.hpp>

#include "DetectionProcessor.h"
#include "DetectionGenerator.h"
#include "Detection.h"
#include "DetectionTracker.h"
#include "BoundedQueue.h"

int main() {
    DetectionGenerator generator_;
    BoundedQueue<Detection> bqueue_(100);
    DetectionProcessor processor_;
    DetectionTracker tracker_;
    std::mutex cout_mutex_;
    std::mutex cv_mutex_;
    std::condition_variable cmd_complete_;
    std::atomic<int> detections_{0};
    std::atomic<int> uid_{0};
    std::atomic<bool>running_{true};
    std::atomic<int> pending_detections_{0};

    std::cout << "---------------------------------------------\n";
    std::cout << "            Simulation activated!\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "               Command Guide                 \n";
    std::cout << "               -------------                 \n";
    std::cout << "           - ten : Detect 10                 \n";
    std::cout << "           - hun : Detect 100                \n";
    std::cout << "           - tho : Detect 1000               \n";
    std::cout << "           - ttho: Detect 10000              \n";
    std::cout << "           - htho: Detect 100000             \n";
    std::cout << "           - h   : Help                      \n";
    std::cout << "           - q   : Quit                      \n";
    std::cout << "---------------------------------------------\n";

    std::string command;

    std::thread producer([&detections_, &generator_, &uid_, &bqueue_, &cout_mutex_, &running_, &pending_detections_, &processor_, &cmd_complete_] () {
        while (running_) {
            if (detections_ > 0) {
                Detection detection = generator_.generate_detection(uid_++);
                {
                    std::lock_guard<std::mutex> lg(cout_mutex_);
                    processor_.validateDetection(detection);
                    std::cout << "[DETECTION] Target " << detection.id << " with signal strength " << detection.signal_strength << ".\n";
                }
                bqueue_.push(detection);
                detections_--;
                pending_detections_++;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
    });

    std::thread consumer([&detections_, &bqueue_, &cout_mutex_, &tracker_, &running_, &pending_detections_, &cmd_complete_, &cv_mutex_] () {
        while (running_) {
            auto detection = bqueue_.pop();
            if (detection != boost::none) {
                std::lock_guard<std::mutex> lg(cout_mutex_);
                std::cout << "[POP] Target " << detection->id << " with signal strength " << detection->signal_strength << "\n";
                tracker_.store_target(*detection);
                std::cout << "[TOTAL] " << tracker_.get_total_detection_count() << "\n";
                cmd_complete_.notify_all();
            }
            
            int remaining = --pending_detections_;
            if (remaining == 0 && detections_ == 0) {
                std::lock_guard<std::mutex> lg(cv_mutex_);
                cmd_complete_.notify_all();
            }
            
            std::this_thread::sleep_for(std::chrono::milliseconds(2));
        }
    });

    while (true) {
        std::cout << "Command: ";
        std::cin >> command;

        if (command == "ten") {
            detections_ = 10;
        } else if (command == "hun") {
            detections_ = 100;
        } else if (command == "tho") {
            detections_ = 1000;
        } else if (command == "ttho") {
            detections_ = 10000;
        } else if (command == "htho") {
            detections_ = 100000; 
        } else if (command == "q") {
            detections_ = 0;
            bqueue_.stop();
            tracker_.stop();
            running_ = false;
            producer.join();
            consumer.join();
            std::cout << "Shutting down simulator. Goodbye!\n";
            return 0;
        } else if (command == "h") {
            detections_ = 0;
            std::cout << "---------------------------------------------\n";
            std::cout << "               Command Guide                 \n";
            std::cout << "               -------------                 \n";
            std::cout << "           - ten : Detect 10                 \n";
            std::cout << "           - hun : Detect 100                \n";
            std::cout << "           - tho : Detect 1000               \n";
            std::cout << "           - ttho: Detect 10000              \n";
            std::cout << "           - htho: Detect 100000             \n";
            std::cout << "           - h   : Help                      \n";
            std::cout << "           - q   : Quit                      \n";
            std::cout << "---------------------------------------------\n";
        } else if (command == "report") {
            detections_ = 0;
            auto map = tracker_.track_all();
            std::cout << "Total:\n";
            for (const auto& pair : map) {
                std::cout << "- " << pair.first << ": (" << pair.second.id << ", " << pair.second.signal_strength << ")\n";
            }
        }

        // NOW wait for the command to complete (if it was a detection command)
        if (command == "ten" || command == "hun" || command == "tho" || 
            command == "ttho" || command == "htho") {
            std::unique_lock<std::mutex> lk(cv_mutex_);
            std::cout << "[WAITING] Processing " << detections_.load() << " detections...\n";
            cmd_complete_.wait(lk, [&detections_, &pending_detections_]() {
                return detections_ == 0 && pending_detections_ == 0;
            });
            std::cout << "[COMPLETE] All detections processed!\n";
        }
    }
}