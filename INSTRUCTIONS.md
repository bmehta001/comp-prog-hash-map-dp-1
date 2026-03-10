# Instructions

## Overview

This assignment contains **6 problems** covering hash maps, dynamic
programming, and linked list implementation. For each problem, you
need to implement the required function(s) in **one** programming
language of your choice (Java, Python, or C++).

## File Structure

```
java/
  TestHarness.java              ← Testing framework (DO NOT MODIFY)
  Question1_MyHashMap.java      ← Your code goes here
  Question1_Tests.java          ← Test cases (DO NOT MODIFY)
  Question2_LinkedList.java
  Question2_Tests.java
  Question3_Fibonacci.java
  Question3_Tests.java
  Question4_Factorial.java
  Question4_Tests.java
  Question5_ClimbStairs.java
  Question5_Tests.java
  Question6_CoinAmounts.java
  Question6_Tests.java
python/
  test_harness.py               ← Testing framework (DO NOT MODIFY)
  question1_my_hash_map.py
  question1_tests.py            ← Test cases (DO NOT MODIFY)
  question2_linked_list.py
  question2_tests.py
  question3_fibonacci.py
  question3_tests.py
  question4_factorial.py
  question4_tests.py
  question5_climb_stairs.py
  question5_tests.py
  question6_coin_amounts.py
  question6_tests.py
cpp/
  test_harness.h                ← Testing framework (DO NOT MODIFY)
  question1_my_hash_map.cpp
  question1_tests.h             ← Test cases (DO NOT MODIFY)
  question2_linked_list.cpp
  question2_tests.h
  question3_fibonacci.cpp
  question3_tests.h
  question4_factorial.cpp
  question4_tests.h
  question5_climb_stairs.cpp
  question5_tests.h
  question6_coin_amounts.cpp
  question6_tests.h
```

## How to Run

### Java
```bash
cd java
javac *.java
java Question1_MyHashMap      # Run question 1
java Question2_LinkedList     # Run question 2
java Question3_Fibonacci      # Run question 3
java Question4_Factorial      # Run question 4
java Question5_ClimbStairs    # Run question 5
java Question6_CoinAmounts    # Run question 6
```

### Python
```bash
cd python
python question1_my_hash_map.py
python question2_linked_list.py
python question3_fibonacci.py
python question4_factorial.py
python question5_climb_stairs.py
python question6_coin_amounts.py
```

### C++
```bash
cd cpp
g++ -std=c++17 -O2 -o q1 question1_my_hash_map.cpp && ./q1
g++ -std=c++17 -O2 -o q2 question2_linked_list.cpp && ./q2
g++ -std=c++17 -O2 -o q3 question3_fibonacci.cpp && ./q3
g++ -std=c++17 -O2 -o q4 question4_factorial.cpp && ./q4
g++ -std=c++17 -O2 -o q5 question5_climb_stairs.cpp && ./q5
g++ -std=c++17 -O2 -o q6 question6_coin_amounts.cpp && ./q6
```

Or use CMake:
```bash
cd cpp
cmake -B build && cmake --build build
./build/question1   # etc.
```

## Quick Mode

During development, use `.runQuick()` (Java/C++) or `.run_quick()`
(Python) instead of `.run()` in the main method. This skips benchmarks
and scaling analysis, running only correctness and random tests.

## What to Implement

### Question 1 — Custom HashMap
Implement a hash map using **open addressing** with **linear probing**
and **dynamic resizing**. A real hash function is provided — you must
figure out how to map its output to a valid array index.
You must fill in: `put()`, `get()`, `containsKey()`, `remove()`, `size()`, `resize()`.
See `HINTS.md` for pseudocode and step-by-step guidance.

### Question 2 — Custom Linked List
Implement a singly linked list from scratch with: `add()`, `get()`,
`remove()`, `contains()`, `size()`, `reverse()`.

### Question 3 — Fibonacci (Four Implementations + Analysis)
**Part A — Code:** Implement four versions of Fibonacci:
1. `fibRecursive(n)` — naive recursion
2. `fibMemoized(n)` — top-down DP with memoization
3. `fibBottomUp(n)` — bottom-up DP filling a dp[] array
4. `fibIterative(n)` — space-optimized iterative (two variables)

**Part B — Analysis:** Answer 12 questions by hand (not by running code):
- Trace the recursive call tree for fib(5) and count calls per fib(k)
- Determine total function calls for recursive and memoized approaches
- State the time and space complexity of each approach

Correct answers unlock detailed feedback explaining *why* each answer
is correct.

### Question 4 — Factorial (Four Implementations + Analysis)
**Part A — Code:** Implement four versions of Factorial:
1. `factRecursive(n)` — naive recursion
2. `factMemoized(n)` — top-down DP with memoization
3. `factBottomUp(n)` — bottom-up DP filling a dp[] array
4. `factIterative(n)` — space-optimized iterative (accumulator)

**Part B — Analysis:** Answer 12 questions by hand (same format as Q3):
- Trace the recursive call tree for factorial(5) and count calls
- Determine total function calls for recursive and memoized approaches
- State the time and space complexity of each approach

Key insight: unlike Fibonacci, factorial has **no overlapping subproblems**.
Discover what that means for memoization's effectiveness!

### Question 5 — Climbing Stairs
Count distinct ways to climb N stairs taking 1 or 2 steps at a time.
Implement three approaches:
1. `solveRecursive(n)` — naive recursion
2. `solveMemoized(n)` — top-down with memoization
3. `solveIterative(n)` — bottom-up iteration

### Question 6 — Coin Combination Amounts
Given coins [1, 5, 10, 25] and N coins to use, count distinct total
amounts formable. Implement three approaches:
1. `solveRecursive(n)` — naive recursion (DFS over all coin choices)
2. `solveMemoized(n)` — top-down with memoization
3. `solveIterative(n)` — bottom-up DP with boolean array

## Grading

The autograder runs your tests automatically on push. Each question
is worth **10 points** (60 total). Points are all-or-nothing per
question — all tests must pass.

## Rules

- **DO NOT** modify any `*_Tests.*` or `*_tests.*` files
- **DO NOT** modify `TestHarness.java`, `test_harness.py`, or `test_harness.h`
- You may add helper methods/functions within your solution files
- You may use standard library data structures **except** for questions
  that ask you to build your own (Q1 HashMap, Q2 Linked List)
