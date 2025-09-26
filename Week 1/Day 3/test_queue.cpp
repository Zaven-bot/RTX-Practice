#include <gtest/gtest.h>
#include "bounded_queue.h"

TEST(BoundedQueueTest, PushPopBasic) {
    bounded_queue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);

    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
}