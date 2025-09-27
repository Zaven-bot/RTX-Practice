// bounded_queue.h

/////////////////////////
//       DECLARE       //
/////////////////////////

#pragma once
#include <mutex>
#include <iostream>
#include <queue>
#include <boost/optional.hpp>

template<typename T>
class bounded_queue {
public:
    explicit bounded_queue(size_t capacity);

    void push(const T& item);
    boost::optional<T> pop(const std::chrono::milliseconds& time = std::chrono::milliseconds(1));
    void stop();

private:
    std::mutex mtx_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    std::queue<T> queue_;
    size_t capacity_;
    bool stopped_ = false;
};

/////////////////////////
//    IMPLEMENTATION   //
/////////////////////////
template<typename T>
// initializer list immediately assigns value of capacity to capacity
bounded_queue<T>::bounded_queue(size_t capacity) : capacity_(capacity) { } 

template<typename T>
void bounded_queue<T>::push(const T& item) {
    std::unique_lock<std::mutex> lock(mtx_);
    // Give up the lock temporarily so other (pop) threads can run
    not_full_.wait(lock, [this] {return queue_.size() < capacity_ || stopped_;});

    // If sys shut down and queue is full, don't add more. Exit gracefully.
    if (stopped_ && queue_.size() >= capacity_) {
        std::cout << "Stopped push\n";
        return; 
    }

    queue_.emplace(item); // Prevents constructing and then copying/moving
    // Signals waiting consumer (pop) thread that the queue is no longer empty
    not_empty_.notify_one();
}

template<typename T>
boost::optional<T> bounded_queue<T>::pop(const std::chrono::milliseconds& time) {
    std::unique_lock<std::mutex> lock(mtx_);
    // Wait for queue to be empty or sys shut down
    not_empty_.wait_for(lock, time, [this] {return !queue_.empty() || stopped_;});

    // If sys shut down and queue empty, exit gracefully. Don't pop more.
    if (stopped_ || queue_.empty()) {
        std::cout << "Stopped pop\n";
        return boost::none;
    }

    // Otherwise, complete thread request
    // Can't utilize auto& since that would reference an
    // address to an item that no longer exists
    T item = std::move(queue_.front()); // Utilizing move to prevent deep copy
    queue_.pop();
    not_full_.notify_one();
    return item;
}

template<typename T>
void bounded_queue<T>::stop() {
    std::unique_lock<std::mutex> lock(mtx_);
    stopped_ = true;
    not_full_.notify_all();
    not_empty_.notify_all();
}