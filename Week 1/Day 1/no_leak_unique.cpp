#include <iostream> // input + output
#include <memory> // smart pointers
#include <mutex> // locks
#include <thread> // threads

// Mutex object
std::mutex my_mutex;

struct Resource {
    Resource() {
        std::cout << "How much chuck could a would chuck chuck if a would chuck could chuck wood?\n";
    }
    ~Resource() {
        std::cout << "Sandy sells shells on the seashore. Damn. How many shells do you think she sold?...\n";
    }
};

void print_func() {
    my_mutex.lock();
    std::cout << "1. Printing from a thread!\n";
    Resource *r1 = new Resource;
    delete r1;
    my_mutex.unlock();
    std::cout << "4. No leaks in the mid function\n";
}

void better_print_func() {
    std::lock_guard<std::mutex> g1(my_mutex);
    std::cout << "1. Printing from a (better) thread!\n";
    std::unique_ptr<Resource> r2(new Resource);
    std::cout << "3. No leaks in the better function, which utilize smart_ptr and lock_guard\n";
}


int main() {
    std::thread t1(print_func);
    std::thread t2(print_func);
    t1.join();
    t2.join();

    std::thread t3(better_print_func);
    std::thread t4(better_print_func);
    t3.join();
    t4.join();

    std::cout << "Run with leaks --atExit -- ./no_leak_unique to see no leaks, for a total of 0 total leaked bytes! :D\n";
    return 0;
}