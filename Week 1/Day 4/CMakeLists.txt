cmake_minimum_required(VERSION 3.10)
project(Day3)

set(CMAKE_CXX_STANDARD 11) # Compile code with this version of C++

# Tell Cmake to build Google Test from cloned repo.
# googletest-build is the folder where CMake will generate build files for it
add_subdirectory(${CMAKE_SOURCE_DIR}/../../googletest googletest-build) 

# Tell Cmake where to find boost files during compilation
include_directories("/usr/local/opt/boost/include")

# Producer-Consumer Demo
# Builds executable producer_consumer
add_executable(producer_consumer producer_consumer.cpp)
target_link_libraries(producer_consumer pthread)

# Unit Tests
add_executable(test_queue test_queue.cpp)
target_link_libraries(test_queue gtest gtest_main pthread)