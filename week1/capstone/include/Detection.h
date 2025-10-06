// include/detection.h
#pragma once
#include <chrono>

struct Detection {
    int id;

    double x;
    double y;
    double z;

    double x_vel;
    double y_vel;
    double z_vel;

    double distance;

    double signal_strength;
    std::chrono::steady_clock::time_point timestamp; // Retrieve timestamp
};