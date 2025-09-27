#!/bin/bash

set -e # exit on error

echo "Cleaning old build..."
cd "/Users/ianunebasami/Documents/RTX-Practice/Week 1/Day 4"
rm -rf build
mkdir build
cd build

echo "Running cmake..."
cmake ..

echo "Running make..."
make

echo "Build complete!"

echo "Running test..."
./test_queue

echo "Test complete!"

echo "Yipee! :D"
