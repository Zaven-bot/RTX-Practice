#include "DetectionProcessor.h"
#include "Detection.h"
#include <iostream>

void DetectionProcessor::validateDetection (Detection d) {
    if (d.signal_strength >= 1) {
        std::cout << "[WARNING] Target " << d.id << " is " << d.distance << " away!\n";
    }
}
