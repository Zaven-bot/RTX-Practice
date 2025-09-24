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


###

Example No. 2
1. Focus (1 sentence): 
        
        - “Studied RAII and smart pointers.”

2. What I built (bullets):

        - file_writer.cpp → RAII with ofstream and smart pointer
        - leak_demo.cpp → intentional leak + leaks output
        - no_leak_unique.cpp → unique_ptr, lock_guard, thread-safe RAII

Key Concepts (bullets, no sentences): 

        - unique_ptr
        - lock_guard
        - leaks
        - lldb
        - etc.

Gotchas (1–2 bullets): 
        
        - “Const with char* vs std::string& confused me.”

Next Step (1 line): 

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
        - no_leak_unique.cpp : Super cool. Utilizes both smart pointers, std::lock_guard<std::lockType> g1(instantiatedSharedLockInstance)
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

        Tried accepting filename as a const char* instead of a const std::string&. I learned that const means you can't modify the string
        you are taking as input. I learned that std::string is safer in term of mem alloc/dealloc. In addition std::string& would allow
        for both std::string and char*, while char* would throw an error with std::string passed in. std::string& is a reference while
        char* is a pointer.

**Next Step / Open Question (2 min)** Define what tomorrow should build on, or note an unresolved issue.

        Continue working on Day 2 requirements.

---




---

## Day 2
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 3
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 4
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 5
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 6
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 7
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

# Week 2

## Day 8
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 9
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 10
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 11
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 12
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 13
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 14
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

# Week 3

## Day 15
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 16
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 17
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 18
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 19
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 20
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 21
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

# Week 4

## Day 22
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 23
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 24
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 25
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 26
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 27
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

## Day 28
**Focus:** 

**What I Built / Practiced:** 

**Key Concepts Learned:** 

**Problems Solved / Debugged:** 

**Design Decisions:** 

**Next Step / Questions for Tomorrow:** 

---

