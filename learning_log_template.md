# Raytheon Prep Learning Log

This document tracks daily progress, key learnings, and reflections over the 4-week prep plan.

### Example:

1. Date + Focus (1 min)

        Today’s main topics: C++ RAII, smart pointers, gdb basics

2. What I Built (2 min) : Summarize code artifacts you wrote or modified.
        
        “Thread-safe queue implementation (C++), tested with producer/consumer threads.”

3. Key Concepts Learned (3 min): Bullet list of 2–3 “aha” moments or pitfalls fixed.

        - unique_ptr transfers ownership automatically, avoids double deletes.
        
        - gdb: bt shows call stack at crash point.

        - Valgrind caught a memory leak from forgetting delete.

4. Gotchas / Mistakes (2 min): Short notes on what tripped you up today.

        - “Tried to copy unique_ptr directly → compile error; need std::move.”

5. Next Step / Open Question (2 min): Define what tomorrow should build on, or note an unresolved issue.

        - “Queue works for ints, but how to template for generic types?”


### Example No. 2
1. Focus (1 sentence): 
        
        - “Studied RAII and smart pointers.”

2. What I built (bullets):

        - file_writer.cpp → RAII with ofstream and smart pointer
        - leak_demo.cpp → intentional leak + leaks output
        - no_leak_unique.cpp → unique_ptr, lock_guard, thread-safe RAII

3. Key Concepts (bullets, no sentences): 

        - unique_ptr
        - lock_guard
        - leaks
        - lldb
        - etc.

4. Gotchas (1–2 bullets): 
        
        - “Const with char* vs std::string& confused me.”

5. Next Step (1 line): 

        - “Move on to threading basics tomorrow.”

---

# Week 1

## Day 1
**Focus:** 

        C++, Resource Acquisition is Initialization (RAII), Resource Deallocation is Destruction (RDID), smart pointers, memory / leak checks
        
**What I Built / Practiced:** 

        I created three files: 
        - file_writer.cpp : Defines a class which utilizes the user's input as a part of the constructor for the FileWriter class.
        Internally, the FileWriter class utilizes the std::ofstream C++ library stream, a smart pointer, and set::getline(std::cin,
        filename) to write an excerpt from SZA's song, the Weekend (LOL), into the file. The smart pointer will, once we exit the
        scope, deallocate memory. However, we have also included a delete in the deconstructor to ensure it will be deallocated
        and will not need to rely on its fail-safe method of scope deallocation.
        - leak_demo.cpp: Allocates a variable pointing to a struct instance and purposefully does not "delete varName" to simulate
        a memory leak. The output of this memory leak is output into leaks_output.txt, utilizing 'leaks --atExit --./leak_demo >
        leaks_output.txt 2>&1'
        - no_leak_unique.cpp : Super cool. Utilizes both smart pointers, std::lock_guard<std::lockType> g1
        (instantiatedSharedLockInstance)
        and std::unique_ptr<Resource> r2(new Resource) to enforce Resource Allocation is Initialization (RAII) property and either
        lock / unlock out of scope or allocate / deallocate out of scope in a thread-safe fashion. 

**Key Concepts Learned:** 

        - std::unique_ptr
        - std::lock_guard
        - leaks CMD
        - lldb CMD
        - clang-tidy CMD
        - -sanitizer flag for compilation
        - <fstream> for file i/o
        - <iostream> for cmd line i/o
        - <memory> for smart pointers
        - <thread> for threaded functions
        - <mutex> for mutex lock

**Gotchas / Mistakes (2 min):** Short notes on what tripped you up today.

        Tried accepting filename as a const char* instead of a const std::string&. I learned that const means you can't modify the 
        string
        you are taking as input. I learned that std::string is safer in term of mem alloc/dealloc. In addition std::string& would allow
        for both std::string and char*, while char* would throw an error with std::string passed in. std::string& is a reference while
        char* is a pointer.

**Next Step / Open Question (2 min)** Define what tomorrow should build on, or note an unresolved issue.

        Threading basics ... (review?) tomorrow! :D

**Notes:**
  - /usr/local/opt/llvm/bin/clang-tidy program.cpp -- -std=c++17 for static analysis
  - or export PATH="/user/local/opt/llvm/bin:$PATH" + source ~/.zshrc + "clang-tidy program.cpp ..."
    - Relays best practices, unsafe practices, modernization suggestions
    - DOES NOT relay buffer overflows or leaks
  - AddressSanitizer with -fsanitize=address flag for memory errors 
    - Relays, use-after-free, buffer overflows, double free, invalid mem access, stack corruption
    - DOES NOT relay memory leaks
  - leaks --atExit -- ./programName for leak detection
  - lldb for low level debugging, step-by-step
- Checkpoint: Sanitizer shows leak on bad code and no leak on RAII version; gdb/valgrind outputs saved.


---

## Day 2
1. **Focus (1 sentence)**: 

        Threads review, race condition, lock_guard / mutex utilization

2. **What I Built / Practiced (bullets):** 

        hello_threads.cpp → utilize threading for two print functions
                 → utilize threading for a shared count, observe wrong count output
                 → fix with lock_guard and mutex
        Jenkins Docker img → view dashboard, explore different functions (eg )

3. **Key Concepts Learned (bullets):** 

        - Threading
        - fstream OS reliance
        - Thread safety: Ability to run code concurrently in multuple processes
                - Lock guard / mutex

4. **Gotchas (1–2 bullets)**: 

        - Creating a class (BestPrinter) and coordinating input/output files with a 
        single filestream
        and lock. Understand design requirements before jumping headfirst.
        - Didn't stay aligned with plan. Took too much time adding complexity. Finish 
        planned files/features
        before adding more.

5. **Next Step / Open Question (2 min)** 

        - Implementing a bounded queue.
        - Watching 30 minutes of Jenkins setup/utilization

---

## Day 3
1. **Focus (1 sentence)**: 

        Implemented a bounded queue which utilized two condition variables for producer and consumer threads.

2. **What I Built / Practiced (bullets):** 

        - bounded_queue.h → Templated bounded queue functions' declarance and definition
        - producer_consumer.cpp → Implementation of bounded_queue with producer and 
        consumer threads, utilizing locks for printing
        - test_queue.cpp → Simple unit test utilizing the google test (gtest) framework
        - CMakeLists.txt → CMake file defining which files needed to be grouped to create 
        executables
                         → Practiced utilizing cmake / make CMDs

3. **Key Concepts Learned (bullets):**

        - Class definitions and Class declarations
                - ClassName::ClassFunction
        - CMake for executable creation
        - C++17, C++11, C++3 awareness
        - Unit testing in C++ with gtest
        - Lock ordering

4. **Gotchas (1–2 bullets)**: 

        - I had used locks haphazardly. This didn't lead to a deadlock, but the printing
        became unpredictable. I'll be more aware of this in practice. I think I'll need to
        look into lock ordering as well.

5. **Next Step / Open Question (2 min)** 

        - Utilizing Jenkins to orchestrate C++ Day 3 code. Also 30 minutes of LinkedIn 
        Jenkins understanding

---

## Day 4
1. **Focus (1 sentence)**: 

        Integrate testing of bounded_queue into a Jenkins pipeline.

2. **What I Built / Practiced (bullets):** 

        - Jenkins Job
        - Jenkins Pipeline General Configuration
        - Jenkinsfile - Pipeline steps
        - Jenkins File Mounting

3. **Key Concepts Learned (bullets):** 

        - Jenkins Pipeline General
                - Disable concurrent builds
                - Discard old builds
                - Continue build after failure
        - Jenkinsfile format:
                pipeline {
                        agent any
                        stages {
                                stage() {
                                        steps {

                                        }
                                }
                                stage() {
                                        steps {

                                        }
                                }
                        }

                        post {
                                always {

                                }
                                success {

                                }
                                failure {

                                }
                        }
                }
        - boost::optional library: enable returning of "None" or any other type. Utilized
        for pop in case the thread is cancelled. boost::optional<T> was the return flag.

4. **Gotchas (1–2 bullets)**: 

        - The utilization of boost::optional and the fact that, with every sh command in pipeline, the
        shell resets its current printed working directory.

5. **Next Step / Open Question (2 min)** 
        
        - Day 5 will be skipped since it seems redundant and also because I got tired that day lol.

---

## Day 5
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 6
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 7
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

# Week 2

## Day 8
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 9
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 10
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 11
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 12
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 13
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 14
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

# Week 3

## Day 15
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 16
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 17
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 18
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 19
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 20
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 21
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

# Week 4

## Day 22
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 23
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 24
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 25
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 26
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 27
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

## Day 28
1. **Focus (1 sentence)**: 

2. **What I Built / Practiced (bullets):** 

3. **Key Concepts Learned (bullets):** 

4. **Gotchas (1–2 bullets)**: 

5. **Next Step / Open Question (2 min)** 
 

---

