#!/bin/bash

set -e # exit on error

echo "Entering /mnt/RTX-Practice/Week 1/Day 4"
cd "/mnt/RTX-Practice/Week 1/Day 4"

echo "Cleaning old build-dir..."
rm -rf build
ls -la

echo "Creating new build-dir..."
mkdir build

echo "Entering build/"
cd build

echo "Running cmake..."
cmake ..

echo "Running make..."
make

echo "Build complete!"