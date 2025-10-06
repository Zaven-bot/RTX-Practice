#include <gtest/gtest.h>
#include <thread>
#include <boost/optional/optional.hpp>
#include <vector>
#include "DetectionTracker.h"

TEST(DetectionTrackerTest, NewTarget) {
    DetectionTracker tracker_;
    DetectionGenerator generator_;
    std::vector<Detection> targets_;
    Detection d = generator_.generate_detection(1);
    Detection e = generator_.generate_detection(2);

    EXPECT_EQ(tracker_.get_total_detection_count(), 0);
    EXPECT_EQ(tracker_.get_uid_count(), 0);

    tracker_.store_target(d);

    EXPECT_EQ(tracker_.get_total_detection_count(), 1);
    EXPECT_EQ(tracker_.get_uid_count(), 1);

    tracker_.store_target(d);

    EXPECT_EQ(tracker_.get_total_detection_count(), 2);
    EXPECT_EQ(tracker_.get_uid_count(), 1);

    tracker_.store_target(e);

    EXPECT_EQ(tracker_.get_total_detection_count(), 3);
    EXPECT_EQ(tracker_.get_uid_count(), 2);
}

TEST(DetectionTrackerTest, Stopped) {
    DetectionTracker tracker_;
    DetectionGenerator generator_;
    std::vector<Detection> targets_;
    Detection d = generator_.generate_detection(1);
    Detection e = generator_.generate_detection(2);

    tracker_.store_target(d);

    tracker_.stop();

    EXPECT_EQ(tracker_.get_total_detection_count(), 1);
    EXPECT_EQ(tracker_.get_uid_count(), 1);

    tracker_.store_target(e);
    tracker_.track_all();
    tracker_.track(1);

    EXPECT_EQ(tracker_.get_total_detection_count(), 1);
    EXPECT_EQ(tracker_.get_uid_count(), 1);
}

TEST(DetectionTrackerTest, ListTargets) {
    DetectionTracker tracker_;
    DetectionGenerator generator_;
    Detection d = generator_.generate_detection(1);
    Detection d1 = generator_.generate_detection(1);
    Detection e = generator_.generate_detection(2);

    tracker_.store_target(d);
    auto ddet = tracker_.track(1);
    ASSERT_TRUE(ddet != boost::none);
    EXPECT_EQ(ddet->id, 1);

    tracker_.store_target(d1);
    auto dodet = tracker_.track(1);
    ASSERT_TRUE(dodet != boost::none);
    EXPECT_EQ(dodet->id, 1);

    // Entries created by both tracks should be different
    ASSERT_TRUE(ddet->signal_strength != dodet->signal_strength);

    tracker_.store_target(e);
    auto edet = tracker_.track(2);
    ASSERT_TRUE(edet != boost::none);
    EXPECT_EQ(edet->id, 2);

    auto map = tracker_.track_all();
    EXPECT_EQ(map.size(), 2);  // Should have 2 unique targets
    EXPECT_TRUE(map.find(1) != map.end());
    EXPECT_TRUE(map.find(2) != map.end());
}