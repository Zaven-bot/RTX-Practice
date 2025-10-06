// include/detection_generator.h
#pragma once
#include <chrono>
#include <cstdlib>       // for rand()
#include <cmath>         // for sqrt()
#include "Detection.h"

// DetectionGenerator
// Purpose: Create simulated Detections of different foreign targets

class DetectionGenerator {
    public:
        Detection generate_detection(int uid);
};