# Detection Tracking System

A high-performance, multi-threaded C++ simulation system for real-time radar detection processing with comprehensive CI/CD pipeline and performance analysis.

## Overview

This project implements a producer-consumer pattern for processing simulated radar detections with thread-safe operations, comprehensive testing, and automated performance analysis.

## Architecture

### Core Components
- **`Detection`**: Data structure containing position, velocity, distance, and signal strength
- **`DetectionGenerator`**: Generates realistic simulated radar detections with randomized properties
- **`DetectionProcessor`**: Validates detections and issues proximity warnings based on signal strength
- **`BoundedQueue<T>`**: Thread-safe producer-consumer queue with timeout and graceful shutdown
- **`DetectionTracker`**: Thread-safe tracking system maintaining detection history per target ID

### Threading Model
| Thread | Responsibility |
|--------|----------------|
| **Main** | Command interface, user interaction, coordination |
| **Producer** | Generate detections, validate signals, queue for processing |
| **Consumer** | Process queued detections, update tracking history |

## 🚀 Quick Start

### Prerequisites
- C++11 compiler (gcc/clang)
- CMake 3.10+
- Boost libraries
- GoogleTest (included as submodule)

### Build & Run
```bash
# Build the project
./scripts/build.sh

# Run unit tests
./scripts/tests.sh

# Start interactive simulation
./scripts/simulation.sh
```

### Simulation Commands
- `ten`, `hun`, `tho`, `ttho`, `htho` - Generate 10, 100, 1K, 10K, 100K detections
- `report` - Display current tracking summary
- `h` - Show help
- `q` - Quit simulation

## 🧪 Testing & Quality

### Unit Tests (GoogleTest)
- **`TestBoundedQueue`**: Thread-safe queue operations, capacity limits, shutdown handling
- **`TestDetectionProcessor`**: Signal validation and warning generation
- **`TestDetectionTracker`**: Multi-target tracking, thread safety, statistics

### Static Analysis
- **cppcheck**: Static code analysis for bugs and style issues
- **clang-tidy**: Advanced static analysis and modernization checks

### Performance Testing
```bash
# Run comprehensive performance analysis
python3 scripts/perf_test.py

# Generate performance visualizations
python3 scripts/plot_latency.py
```

**Performance Metrics Generated:**
- Latency vs. detection count analysis
- Throughput measurements
- Processing time comparisons
- Visual performance reports

## CI/CD Pipeline

### Jenkins Integration
Complete automated pipeline with Docker containerization:

```bash
# Start Jenkins with pre-configured environment
cd Jenkins
docker-compose up -d
```

**Pipeline Stages:**
1. **Setup** - Environment preparation and cleanup
2. **Configure** - CMake build configuration
3. **Static Analysis** - cppcheck + clang-tidy
4. **Build** - Compile all targets
5. **Unit Testing** - Execute all test suites
6. **Integration Testing** - End-to-end simulation tests
7. **Performance Testing** - Automated performance analysis
8. **Reporting** - Generate and archive performance visualizations

### Container Environment
- Jenkins LTS with C++ toolchain
- Pre-installed: CMake, Boost, cppcheck, clang-tidy
- Python environment with matplotlib/pandas for analysis
- Persistent volume for Jenkins configuration

## Technical Implementation

### Thread Safety Features
- **Mutex protection** for shared data structures
- **Condition variables** for efficient producer-consumer coordination
- **Atomic counters** for lock-free statistics tracking
- **Graceful shutdown** mechanism across all threads

### Key Design Patterns
- **Producer-Consumer** with bounded queue
- **Observer pattern** for detection validation
- **Template-based** generic queue implementation
- **RAII** for automatic resource management

### Performance Optimizations
- Lock-free atomic operations for counters
- Efficient move semantics in queue operations
- Minimal lock contention
- Timeout-based operations to prevent deadlocks

## Learning Outcomes

This project demonstrates mastery of:
- **Concurrent Programming**: Multi-threading, synchronization primitives, race condition prevention
- **Modern C++**: RAII, move semantics, template programming, STL containers
- **Software Engineering**: Unit testing, static analysis, CI/CD, documentation
- **Performance Analysis**: Profiling, metrics collection, visualization
- **DevOps**: Containerization, automated testing, pipeline orchestration

### Synchronization Techniques Used
- `std::mutex` + `std::lock_guard` for basic protection
- `std::unique_lock` + `std::condition_variable` for producer-consumer coordination
- `std::atomic` for lock-free statistics
- Timeout-based operations for graceful degradation

## Project Structure
```
capstone/
├── include/          # Header files
├── src/             # Implementation files
├── tests/           # Unit tests (GoogleTest)
├── scripts/         # Build and analysis automation
├── results/         # Generated reports and metrics
├── CMakeLists.txt   # Build configuration
└── Jenkinsfile      # CI/CD pipeline definition
```