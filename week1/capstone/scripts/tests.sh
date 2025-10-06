#!/bin/bash

echo "🦾 Navigating to build folder..."
cd "/Users/ianunebasami/Documents/RTX-Practice/week1/capstone/build"

echo "🦾 Starting tests..."

echo "🦾 Starting TestBoundQueue Tests (1/3)..."
./TestBoundedQueue

echo "🦾 Starting TestDetectionProcessor Tests (2/3)..."
./TestDetectionProcessor

echo "🦾 Starting TestDetectionTracker Tests (3/3)..."
./TestDetectionTracker

echo "🦾 All tests completed!"
