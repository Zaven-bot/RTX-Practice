# 4-Week Raytheon Prep — Daily Printable Checklist
**Format:** For each day, complete Deep Work → Integration → Learning. Mark checkboxes as you finish. Keep daily log (10 min).

---

## Week 1 — Foundations: C++, Threading, Debugging, Jenkins MVP

### Day 1 — RAII & Smart Pointers + Debug Setup
- [ ] Goal: Understand RAII; run sanitizers and gdb/valgrind basics.
- Deep Work:
  - [X] Read RAII / smart pointer primer (30m)
  - [X] Write `leak_demo.cpp` (manual new/delete) and run AddressSanitizer
  - [X] Write `no_leak_unique.cpp` with `std::make_unique`; confirm no leak
  - [X] Implement `FileWriter` RAII class and test
- Integration:
  - [X] Install lldb and clang-tidy
  - [X] Create `crash.cpp`, debug with gdb (run → bt → print)
  - [X] Run leaks on leak demo, save output
- Learning:
  - [X] Write Day 1 log (what, issues, 1 question)

### Day 2 — Threads & Race Conditions
- [X] Goal: Reproduce & fix a race; run ThreadSanitizer/Helgrind.
- Deep Work:
  - [X] `hello_threads.cpp` (2 threads) → → →  I did like 35 lol
  - [X] Shared counter (no locking) → observe wrong result
  - [X] Fix with `std::mutex` (`lock_guard`)
- Integration:
  - [X] Compile/run with `-fsanitize=thread`; observe detection
- Learning:
  - [X] Jenkins warm-up: run Jenkins Docker image, view dashboard
- Checkpoint: Race reproduced and fixed; sanitizer output captured.

### Day 3 — Producer/Consumer (Condition Variables)
- [X] Goal: Implement bounded queue with `condition_variable`.
- Deep Work:
  - [X] Implement `bounded_queue` (capacity, push/pop blocking)
  - [X] Create `producer_consumer.cpp` demo
- Integration:
  - [X] Add simple test (`test_queue.cpp`) and `build.sh`
  - [X] Run `clang-tidy` on queue sources
- Learning:
  - [X] Read notes on bounded-memory real-time patterns
- Checkpoint: Queue blocks/unblocks correctly; tests run.

### Day 4 — Queue polish + Jenkins MVP
- [X] Goal: Graceful shutdown + Jenkins job builds/tests.
- Deep Work:
  - [X] Add `stop()` and timeout pop to queue
- Integration:
  - [X] Create `Jenkinsfile` (Build → Test stages)
  - [X] Configure Jenkins job to run `build.sh` and `run_tests.sh`
- Learning:
  - [X] Ada syntax overview (read-only)
- Checkpoint: Jenkins job completes successfully (green run).

### Day 5 — Finishups & Retrospective
- [X] Goal: Stabilize Week 1 artifacts and retro.
- Morning:
  - [X] Fix any failing tests
  - [X] Ensure `build.sh` & `run_tests.sh` robust
- Afternoon (Retro):
  - [X] Confirm Week 1 success checklist
  - [X] Rescope Week 2 if needed
- Checkpoint: All Week 1 must-haves complete.

---

## Week 2 — Capstone Core: 2-thread MVP → tests → Jenkins integration

### Day 6 — Capstone repo & design
- [ ] Goal: Repo skeleton and 1-page design brief.
- Deep Work:
  - [ ] Create repo structure, Detection struct header
- Integration:
  - [ ] Configure CMake (or build scripts) and `Jenkinsfile` placeholder
- Learning:
  - [ ] Write concise design brief (must-have features)
- Checkpoint: Repo skeleton committed; brief saved.

### Day 7 — Detection Generator (Thread 1)
- [ ] Goal: Implement generator pushing every 100ms.
- Deep Work:
  - [ ] Implement `DetectionGenerator` using `DetectionQueue`
- Integration:
  - [ ] Unit test for generator timing (~100ms tolerance)
- Learning:
  - [ ] Stub Python injector for future tests
- Checkpoint: Generator pushes messages correctly.

### Day 8 — Signal Processor (Thread 2)
- [ ] Goal: Implement processor that pops, transforms, pushes.
- Deep Work:
  - [ ] Implement `SignalProcessor` with timeout pop
- Integration:
  - [ ] Run both threads and verify pipeline output
- Learning:
  - [ ] Create `run_integration.sh` to run demo & log outputs
- Checkpoint: Pipeline works end-to-end locally.

### Day 9 — Jenkins: build capstone & archive logs
- [ ] Goal: Jenkins builds capstone, runs tests, archives logs.
- Deep Work:
  - [ ] Ensure unit tests for queue/generator/processor
- Integration:
  - [ ] Update Jenkinsfile to run integration script and archive `results/`
- Learning:
  - [ ] Add latency test stub (<200ms)
- Checkpoint: Jenkins job shows tests & archived `log.csv`.

### Day 10 — Optional TrackManager (third thread) or stabilize
- [ ] Goal: Add simple tracking or harden existing pipeline.
- Deep Work:
  - [ ] Implement minimal TrackManager (associate nearby detections)
- Integration:
  - [ ] Re-run integration tests and Jenkins
- Learning:
  - [ ] Document queue sizes/timeouts choices
- Checkpoint: Tracks printed or pipeline solid.

### Day 11 — Unit testing & static analysis
- [ ] Goal: Add more tests and static analysis stage.
- Deep Work:
  - [ ] Add GoogleTest cases for edge cases
- Integration:
  - [ ] Add `cppcheck`/`clang-tidy` to Jenkins (report only)
- Learning:
  - [ ] Improve README with build/run steps
- Checkpoint: Tests pass; static analysis runs.

### Day 12 — Python test harness & latency analysis
- [ ] Goal: Python inject & measure latency; save plot.
- Deep Work:
  - [ ] Implement `perf_test.py` injecting detections and collecting latencies
- Integration:
  - [ ] Run and save `latency_report.png` and `metrics.txt`
- Learning:
  - [ ] Script included in Jenkins as reporting step (optional)
- Checkpoint: Latency report generated and archived.

### Day 13 — Polish & Retrospective
- [ ] Goal: Stabilize capstone and finalize week retro.
- Morning:
  - [ ] Fix flaky tests, ensure pipeline stable
- Afternoon (Retro):
  - [ ] Decide deferred enhancements
- Checkpoint: Week 2 success checklist complete.

---

## Week 3 — Cross-language & Analysis: Ada, MATLAB/Octave, Python automation, docs

### Day 14 — Ada setup & hello world
- [ ] Goal: GNAT installed; run simple Ada program.
- Deep Work:
  - [ ] Install GNAT and run `hello_ada.adb`
- Integration:
  - [ ] Read a small Ada concurrent example and map to C++
- Learning:
  - [ ] Document Ada→C++ mapping in `docs/ada-notes.md`
- Checkpoint: Ada program runs and notes saved.

### Day 15 — Ada reading + small modification
- [ ] Goal: Modify an Ada sample and recompile.
- Deep Work:
  - [ ] Change a small behavior in an Ada queue example
- Integration:
  - [ ] Commit the change and note compile/run commands
- Learning:
  - [ ] Add reading tips for Ada codebases
- Checkpoint: Modified Ada sample compiles and runs.

### Day 16 — MATLAB/Octave basics for log analysis
- [ ] Goal: Import `results/log.csv` and plot basic metrics.
- Deep Work:
  - [ ] Load CSV in Octave/MATLAB and plot latency/tracks
- Integration:
  - [ ] Save `plot.png` and short analysis `analysis.md`
- Learning:
  - [ ] Document required CSV format for logs
- Checkpoint: Plot(s) generated and saved.

### Day 17 — Python regression tests & CI integration
- [ ] Goal: Regression tests automated and in Jenkins.
- Deep Work:
  - [ ] Write `tests/regression.py` to run scenarios & assert no data loss
- Integration:
  - [ ] Add script to Jenkins and archive outputs
- Learning:
  - [ ] Document how to run regression locally vs CI
- Checkpoint: Regression script runs in CI and exits cleanly.

### Day 18 — Technical brief & presentation prep
- [ ] Goal: 1-page technical brief and 5-minute walkthrough.
- Deep Work:
  - [ ] Finalize `docs/technical-brief.md` with architecture and metrics
- Integration:
  - [ ] Attach MATLAB plots and Jenkins logs to brief
- Learning:
  - [ ] Practice 5-minute walkthrough (record)
- Checkpoint: Brief ≤1 page and review-ready.

### Day 19 — Optional Ada port / integration tests
- [ ] Goal: Port small module to Ada or add integration tests (if ahead)
- Deep Work:
  - [ ] Attempt small Ada port OR write more integration tests
- Integration:
  - [ ] Run CI with these tests
- Learning:
  - [ ] Note lessons learned from porting
- Checkpoint: Optional tasks completed or deferred.

### Day 20 — Week 3 retro & stabilization
- [ ] Goal: Ensure Week 3 items completed and CI stable.
- Morning:
  - [ ] Fix CI flakiness, update docs
- Afternoon:
  - [ ] Retro and plan Week 4
- Checkpoint: Week 3 success checklist complete.

---

## Week 4 — Professional polish: presentation, interviews, portfolio

### Day 21 — Slide deck & rehearsal
- [ ] Goal: 10-minute slide deck + rehearsal.
- Deep Work:
  - [ ] Create slides (Problem, Architecture, CI, Results, Lessons)
- Integration:
  - [ ] Record a timed 10-minute run-through
- Learning:
  - [ ] Update slides based on recording
- Checkpoint: Deck ready, timed ≤10 min.

### Day 22 — Mock code review & Q&A
- [ ] Goal: Defend design choices and answer common questions.
- Deep Work:
  - [ ] Prepare concise answers for likely reviewer questions
- Integration:
  - [ ] Perform mock review (record or partner)
- Learning:
  - [ ] Add Q&A to `docs/qa.md`
- Checkpoint: Can defend tradeoffs clearly.

### Day 23 — Portfolio & resume update
- [ ] Goal: Package project artifacts and update resume.
- Deep Work:
  - [ ] Create `portfolio/` page with demo script, metrics, Jenkins screenshot
- Integration:
  - [ ] Run final Jenkins build and archive artifacts
- Learning:
  - [ ] Craft 2 resume bullets with measurable outcomes
- Checkpoint: Portfolio assembled and resume updated.

### Day 24 — Algorithm & system design practice
- [ ] Goal: Quick algorithm practice + system-design whiteboard.
- Deep Work:
  - [ ] Solve 2 medium easy problems (arrays/hashmaps) in 30–40 min
- Integration:
  - [ ] Do 5-minute whiteboard design of sensor pipeline
- Learning:
  - [ ] Note common pitfalls in answers
- Checkpoint: Can solve a medium problem in allotted time.

### Day 25 — Buffer day (finishups only)
- [ ] Goal: Finish any missed items; do not add new big tasks.
- Tasks:
  - [ ] Complete outstanding testing/docs/CI issues
  - [ ] Light polish on project
- Checkpoint: Core deliverables complete.

### Day 26 — Final dress rehearsal (demo + presentation)
- [ ] Goal: Full demo + presentation run.
- Deep Work:
  - [ ] Run `run_integration.sh` and capture logs
- Integration:
  - [ ] Present live demo and Q&A rehearsal
- Learning:
  - [ ] Note last-minute fixes
- Checkpoint: Demo runs cleanly and slides match demo.

### Day 27 — First-week-on-job plan
- [ ] Goal: Prepare 30-day onboarding plan for manager.
- Tasks:
  - [ ] Draft Week1/Week2 objectives and learning goals
  - [ ] Prepare list of questions to ask on day 1
- Checkpoint: 1-page onboarding plan ready.

### Day 28 — Relaxed review & confidence building
- [ ] Goal: Light review; rest and confidence-building
- Tasks:
  - [ ] Review notes, 1-minute pitch, and slide highlights
  - [ ] Relax and celebrate progress
- Checkpoint: Ready and energized for Day 1.

---

## Quick Reference (one-liners)
- AddressSanitizer compile: `g++ -g -fsanitize=address -std=c++17`
- ThreadSanitizer compile: `g++ -g -fsanitize=thread -std=c++17`
- Valgrind memcheck: `valgrind --leak-check=full ./program`
- gdb: `gdb ./program` → `run` → `bt` → `print var`
- Jenkins local (Docker): `docker run -p 8080:8080 jenkins/jenkins:lts`

---

**Usage:** Print this file or open in a markdown viewer. Check off items every day and keep minimal logs in `docs/daily-logs/`.