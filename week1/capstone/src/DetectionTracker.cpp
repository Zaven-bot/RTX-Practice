#include "DetectionTracker.h"
#include <iostream>

void DetectionTracker::store_target(Detection detection) {
    std::unique_lock<std::mutex> lock(mtx_);
    if (stopped_) {
        std::cout << "DetectionTracker: System shut down. Cancelled store.\n";
        return;
    }
    auto it = umap.find(detection.id);
    if (it != umap.end()) {
        it->second.push_back(detection);
    } else {
        umap[detection.id] = std::vector<Detection>{detection};
        unique++;
    }
    total++;
}

boost::optional<Detection> DetectionTracker::track(int uid) {
    std::unique_lock<std::mutex> lock(mtx_);
    if (stopped_) {
        std::cout << "DetectionTracker: System shut down. Cancelled track.\n";
        return boost::none;
    }
    if (umap.find(uid) != umap.end()) {
        return umap[uid].back();
    } else {
        return boost::none;
    }
}

std::unordered_map<int, Detection> DetectionTracker::track_all() {
    std::unique_lock<std::mutex> lock(mtx_);
    if (stopped_) {
        std::cout << "DetectionTracker: System shut down. Cancelled track all.\n";
        return {};
    }
    std::unordered_map<int, Detection> scan;
    for (const auto& pair : umap) {
        scan[pair.first] = pair.second.back();
    }
    return scan;
}

int DetectionTracker::get_total_detection_count() {
    std::unique_lock<std::mutex> lock(mtx_);
    return total;
}

int DetectionTracker::get_uid_count() {
    std::unique_lock<std::mutex> lock(mtx_);
    return unique;
}

void DetectionTracker::stop() {
    std::unique_lock<std::mutex> lock(mtx_);
    stopped_ = true;
}