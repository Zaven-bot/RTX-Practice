#include "bounded_queue.h"
#include <thread>
#include <iostream>

int main() {
    std::mutex cout_mutex;
    bounded_queue<int> q(5);
    std::vector<std::thread> threads;
    for (int i = 0; i < 25; i++) {
        threads.emplace_back([i, &q, &cout_mutex] () {
            q.push(i);
            // Locks for cout are only acquired once printing
            // can be done
            std::lock_guard<std::mutex> lock(cout_mutex); 

            std::cout << "Producer thread " << i << " has been pushed.\n";
        });
    }
    for (int i = 0; i < 25; i++) {
        threads.emplace_back([&q, &cout_mutex] () { 
            int item = q.pop();
            // Ditto ^^
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "Consumer thread " << item << " has been popped.\n";
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }
    
    return 0;
}