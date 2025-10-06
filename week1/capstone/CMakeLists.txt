cmake_minimum_required(VERSION 3.10)
project(Capstone)

set(CMAKE_CXX_STANDARD 11) # Compile code with this version of C++
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell Cmake to build Google Test from cloned repo.
# googletest-build is the folder where CMake will generate build files for it
add_subdirectory(${CMAKE_SOURCE_DIR}/../../googletest googletest-build) 

# Tell Cmake where to find boost files during compilation
find_package(Boost REQUIRED COMPONENTS thread)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

# Producer-Consumer Demo
# Builds executable producer_consumer
add_executable(producer_consumer src/producer_consumer.cpp)
target_link_libraries(producer_consumer pthread)

# Unit Tests
add_executable(TestBoundedQueue tests/TestBoundedQueue.cpp)
target_link_libraries(TestBoundedQueue gtest gtest_main pthread)

add_executable(TestDetectionTracker tests/TestDetectionTracker.cpp src/DetectionTracker.cpp src/DetectionGenerator.cpp)
target_link_libraries(TestDetectionTracker gtest gtest_main pthread)

add_executable(TestDetectionProcessor tests/TestDetectionProcessor.cpp src/DetectionProcessor.cpp src/DetectionGenerator.cpp)
target_link_libraries(TestDetectionProcessor gtest gtest_main)

# Simulation
add_executable(Simulation src/Simulation.cpp src/DetectionTracker.cpp src/DetectionGenerator.cpp src/DetectionProcessor.cpp)
target_link_libraries(Simulation pthread)