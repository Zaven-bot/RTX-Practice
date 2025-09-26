// bounded_queue.h

/////////////////////////
//       DECLARE       //
/////////////////////////

#pragma once
#include <mutex>
#include <iostream>
#include <queue>

template<typename T>
class bounded_queue {
public:
    explicit bounded_queue(size_t capacity);

    void push(const T& item);
    T pop();

private:
    std::mutex mtx_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
    std::queue<T> queue_;
    size_t capacity_;
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
    not_full_.wait(lock, [this] {return queue_.size() < capacity_;});
    queue_.emplace(item); // Prevents constructing and then copying/moving
    // Signals waiting consumer (pop) thread that the queue is no longer empty
    not_empty_.notify_one();
}

template<typename T>
T bounded_queue<T>::pop() {
    std::unique_lock<std::mutex> lock(mtx_);
    not_empty_.wait(lock, [this] {return !queue_.empty();});
    // Can't utilize auto& since that would reference an
    // address to an item that no longer exists
    T item = std::move(queue_.front()); // Utilizing move to prevent deep copy
    queue_.pop();
    not_full_.notify_one();
    return item;
}