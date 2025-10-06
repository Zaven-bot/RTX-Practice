#!/bin/bash

echo "Navigating to build-dir..."

cd build

echo "Executing test_queue..."

./test_queue

echo "Finished executing tests!"
