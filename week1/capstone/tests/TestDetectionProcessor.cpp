#include <gtest/gtest.h>
#include "DetectionProcessor.h"
#include "Detection.h"
#include "DetectionGenerator.h"

TEST(DetectionProcessorTest, DetectOne) {
    DetectionGenerator generator_;
    DetectionProcessor processor_;
    Detection d = generator_.generate_detection(1);
    d.signal_strength = 1;
    processor_.validateDetection(d);

    SUCCEED();
}