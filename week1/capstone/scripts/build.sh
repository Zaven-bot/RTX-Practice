#!/bin/bash

set -e # exit on error

echo "Cleaning old build..."
cd "/Users/ianunebasami/Documents/RTX-Practice/week1/capstone"
rm -rf build
mkdir build
cd build

echo "Running cmake..."
cmake ..

echo "Running make..."
make

echo "Build complete!"