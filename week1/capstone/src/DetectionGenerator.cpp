#include "DetectionGenerator.h"

Detection DetectionGenerator::generate_detection(int uid) {
    Detection d;

    d.id = uid;

    d.x = rand() % 1000;
    d.y = rand() % 1000;
    d.z = rand() % 100;

    d.x_vel = (rand() % 20) - 10; // -10 m/s -> 10 m/s
    d.y_vel = (rand() % 20) - 10;
    d.z_vel = (rand() % 10) - 5; // -5 m/s -> 5 m/s

    d.distance = sqrt(d.x * d.x + d.y * d.y + d.z * d.z);

    d.signal_strength = 1000 / (d.distance + 1);

    d.timestamp = std::chrono::steady_clock::now();

    return d;
}