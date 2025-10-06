// include/DetectionTracker.h
#pragma once
#include <unordered_map>
#include <vector>
#include <chrono>
#include <mutex>
#include <atomic>
#include <boost/optional.hpp>
#include "Detection.h"
#include "DetectionGenerator.h"


// Track simulated detections from DetectionGenerator
class DetectionTracker {
    protected:
        std::mutex mtx_;
        int next_id;
        std::atomic<int> total{0};
        std::atomic<int> unique{0};
        bool stopped_ = false;
        std::unordered_map<int, std::vector<Detection>> umap;
    public:
        DetectionTracker() {};
        // Store a detection from BoundedQueue
        void store_target(Detection d);
        // Track one target most recent Detection stat by uid
        boost::optional<Detection> track(int uid);
        // Track all targets most recent Detection stat
        std::unordered_map<int, Detection> track_all();
        // Provides counts of total detections
        int get_total_detection_count();
        // Provides counts of total unique detection uids
        int get_uid_count();
        // Stops system
        void stop();
};