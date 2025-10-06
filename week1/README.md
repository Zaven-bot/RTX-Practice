# Detection Tracking Simulation

Multi-threaded C++ simulation for radar detection processing

## Architecture
- **DetectionGenerator**: Generate simulated detections
- **DetectionProcessor**: Validates signal strength
- **BoundedQueue**: Thread-safe consumer-producer queue
- **DetectionTracker**: Thread-safe hashmap for Detection tracking history

## Build Instructions
```bash
mkdir build && cd build
cmake ..
make
```

## Running Tests
```bash
./build/TestBoundedQueue
./build/TestDetectionProcessor
./build/TestDetectionTracker
```

## Running Simulation
```bash
./Simulation
```

## CI/CD
- Create the Jenkins instance with the Jenkins directory in root
- Copy + Paste the Jenkinsfile in this directory and run the job

## Retrospective
In this project, I learned the use cases for lock_guard's and unique_lock's (wait, notify one, notify all), and utilized the mutex lock for most of my locking operations. The locks were used to ensure there would be no std::cout corruption and that no R/W operations would be occurring at the same time in either the "unordered_map" (DetectionTracker) or the "queue" (BoundedQueue). In a similar vein, I learned how to use the atomic marker for booleans or integers that needed to be accessed atomically for accurate counts and increments. That said, these are all counter measures for when multiple threads are accessing the same information. In our main simulation, we utilized 3 threads -> consumer, producer, and main. The threads were initialized using  lambda-based thread constructors which utilized the '[]' (capture list), () (parameters), and {} (predicate). What helped coordinate
a great half of the logic are the condition variables: they ensured the bounded_queue would only push or pull once
the requirements were met and ensured the prints from the simulation came out in the correct order.


| Thread    | Role                                 |
|-----------|--------------------------------------|
| main      | UI loop, command dispatch, shutdown  |
| producer  | Generates and queues detections      |
| consumer  | Processes and tracks detections      |
