#include <gtest/gtest.h>
#include "BoundedQueue.h"
#include <thread>
#include <boost/optional/optional_io.hpp>
#include <vector>

TEST(BoundedQueueTest, PushPopBasic) {
    BoundedQueue<int> q(3);
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), 2);
    EXPECT_EQ(q.pop(), 3);
    EXPECT_EQ(q.pop(), 4);
}

TEST(BoundedQueueTest, InvalidPop) {
    BoundedQueue<int> q(3);
    EXPECT_EQ(q.pop(), boost::none);
    q.push(1);
    EXPECT_EQ(q.pop(), 1);
    EXPECT_EQ(q.pop(), boost::none);
    EXPECT_EQ(q.pop(), boost::none);
}

TEST(BoundedQueueTest, MidStop) {
    std::mutex mtx_;
    BoundedQueue<int> q(3);
    std::vector<std::thread> threads;
    for (int i = 0; i < 25; i++) {
        if (i % 2 == 0) {
            threads.emplace_back([i, &q, &mtx_] () {
                q.push(i);
                std::lock_guard<std::mutex> lg_(mtx_);
                std::cout << "[PUSH] with thread " << i << "!\n";
            });
        }
        if (i % 3 == 0) {
            threads.emplace_back([i, &q, &mtx_] () {
                q.pop();
                std::lock_guard<std::mutex> lg_(mtx_);
                std::cout << "[POP] with thread " << i << "!\n";
            });
        }
        if (i == 16) {
            threads.emplace_back([i, &q, &mtx_] () {
                q.stop();
                std::lock_guard<std::mutex> lg_(mtx_);
                std::cout << "Activated stop flag!\n";
            }); 
        }
    }

    for (auto& thread : threads) {
        thread.join();
    }
}