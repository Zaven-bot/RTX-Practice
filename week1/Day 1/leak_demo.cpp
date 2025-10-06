// When compiling this code with on mac, utilize:
// clang++ -g -o leak_demo leak_demo.cpp
    // -g : debug symbols for better error messages
    // -o : name output executable
// Run executable and then run leaks --atExit -- ./leak_demo

#include <iostream> // Input and Output
#include <memory> // Smart pointers

struct Resource {
    Resource() { std::cout << "Resource object created!\n";}
    ~Resource() { std::cout << "Resource object destroyed!\n";}
};

int main() {
    // Manually allocate memory
    Resource *r1 = new Resource;
    std::cout << "Resource object still alive!\n";
    // Manually deallocate memory
    // delete r1;

    std::unique_ptr<Resource> r2(new Resource);
    return 0;
}