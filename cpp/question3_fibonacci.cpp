/**
 * ===============================================================
 *  PROBLEM 3 — Fibonacci: Four Implementations + Analysis
 * ===============================================================
 *
 *  The Fibonacci sequence is defined as:
 *    F(0) = 0
 *    F(1) = 1
 *    F(n) = F(n-1) + F(n-2)   for n >= 2
 *
 *  First few values: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...
 *
 *  ===============================================================
 *   PART A — Code Implementations
 *  ===============================================================
 *
 *  Implement FOUR different approaches to compute F(n):
 *
 *  --- Approach 1: Naive Recursive --------------------------------
 *  Direct translation of the recurrence relation.
 *  Think about: why is this so slow?
 *
 *  --- Approach 2: Memoized (Top-Down DP) -------------------------
 *  Same recursive structure, but cache results in a
 *  std::vector<long long> or a plain array.
 *  Before computing F(k), check if it's already been computed.
 *
 *  --- Approach 3: Bottom-Up DP (Array) ---------------------------
 *  Build the answer from F(0) up to F(n) using a dp vector/array.
 *  Fill dp[0], dp[1], then dp[i] = dp[i-1] + dp[i-2] for i >= 2.
 *
 *  --- Approach 4: Iterative (Two Variables) ----------------------
 *  Same bottom-up idea, but instead of storing the whole array,
 *  keep only the two most recent values.
 *
 *  ===============================================================
 *   PART B — Analysis Questions
 *  ===============================================================
 *
 *  The main goal of this problem is for you to TRACE through the
 *  recursive calls and DISCOVER the time/space complexity yourself.
 *
 *  Below are functions that return YOUR answers. Fill them in by
 *  hand (not by running code). The test harness will check them.
 *
 *  When you get an answer correct, you'll see detailed feedback
 *  explaining WHY that answer is correct.
 *
 *  Compile & run:
 *    g++ -std=c++17 -O2 question3_fibonacci.cpp -o q3 && ./q3
 *    cl /std:c++17 /EHsc /O2 question3_fibonacci.cpp /Fe:q3.exe && q3.exe
 * ===============================================================
 */

#include "test_harness.h"
#include <vector>
#include <string>

// ===============================================================
//  PART A — Code Implementations
// ===============================================================

long long fibRecursive(int n) {
    // TODO: Implement naive recursive fibonacci
    // Base cases: fib(0) = 0, fib(1) = 1
    // Recursive case: fib(n) = fib(n-1) + fib(n-2)
    return -1;
}

long long fibMemoized(int n) {
    // TODO: Implement memoized (top-down DP) fibonacci
    // Create a std::vector<long long> memo of size n+1, initialized to -1
    // Use a helper function that takes (n, memo)
    // If memo[n] != -1, return it (already computed)
    // Otherwise compute, store in memo, and return
    return -1;
}

long long fibBottomUp(int n) {
    // TODO: Implement bottom-up DP fibonacci with an array
    // Create a std::vector<long long> dp of size n+1
    // Set dp[0] = 0, dp[1] = 1
    // Fill dp[i] = dp[i-1] + dp[i-2] for i from 2 to n
    // Return dp[n]
    return -1;
}

long long fibIterative(int n) {
    // TODO: Implement iterative fibonacci with two variables
    // Use two variables: prev = 0, curr = 1
    // Loop from 2 to n, updating: next = prev + curr
    // No array needed — just shift the two variables each iteration
    return -1;
}

// ===============================================================
//  PART B — Analysis Questions
//
//  Answer these by tracing through the code BY HAND.
//  You'll learn the most by working through these on paper
//  rather than just running the code.
// ===============================================================

/**
 * B1: When fibRecursive(5) runs, how many times is each fib(k) called?
 *
 * Return a vector of length 6 where index k = number of times fib(k)
 * is called. For example, if fib(3) is called 2 times, vec[3] = 2.
 *
 * Hint: draw the full call tree on paper starting from fib(5).
 * fib(5) calls fib(4) and fib(3). Then fib(4) calls fib(3) and fib(2).
 * Keep going until you reach base cases fib(1) and fib(0).
 * Count how many times each fib(k) appears in your tree.
 */
std::vector<int> callCountsFib5() {
    // TODO: Fill in the call counts for fib(0) through fib(5)
    //       vec[0] = times fib(0) is called
    //       vec[1] = times fib(1) is called
    //       ...
    //       vec[5] = times fib(5) is called
    return {0, 0, 0, 0, 0, 0};
}

/**
 * B2: What is the TOTAL number of function calls made by fibRecursive(5)?
 * Count every call, including the initial call to fib(5) itself.
 */
int totalCallsRecursive5() {
    // TODO: Return the total number of calls
    return 0;
}

/**
 * B3: What is the TOTAL number of function calls made by fibRecursive(10)?
 * You don't need to draw the full tree — find the pattern from smaller examples.
 *
 * Hint: Let T(n) = total calls for fibRecursive(n).
 * T(0) = 1, T(1) = 1. What is T(n) in terms of T(n-1) and T(n-2)?
 */
int totalCallsRecursive10() {
    // TODO: Return the total number of calls
    return 0;
}

/**
 * B4: What is the TOTAL number of function calls made by fibMemoized(5)?
 * With memoization, each fib(k) is computed at most once.
 * But there are still calls that hit the cache and return immediately.
 *
 * Hint: trace through the memoized version. The first time fib(k) is
 * called, it recurses. The second time, it returns from the cache
 * immediately (still counts as a call, but no further recursion).
 */
int totalCallsMemoized5() {
    // TODO: Return the total number of calls
    return 0;
}

// --- Complexity Questions ----------------------------------------
//
// For each approach, state the time and space complexity.
// Return EXACTLY one of these strings:
//   "O(1)", "O(N)", "O(N^2)", "O(2^N)"
//
// Think about:
//   Time  = how many operations as N grows?
//   Space = how much extra memory (beyond the input)?
//           For recursive approaches, consider the call stack.

/** B5: Time complexity of fibRecursive(n) */
std::string timeComplexityRecursive() {
    return "";
}

/** B6: Space complexity of fibRecursive(n) — think about call stack depth */
std::string spaceComplexityRecursive() {
    return "";
}

/** B7: Time complexity of fibMemoized(n) */
std::string timeComplexityMemoized() {
    return "";
}

/** B8: Space complexity of fibMemoized(n) — memo vector + call stack */
std::string spaceComplexityMemoized() {
    return "";
}

/** B9: Time complexity of fibBottomUp(n) */
std::string timeComplexityBottomUp() {
    return "";
}

/** B10: Space complexity of fibBottomUp(n) — the dp[] vector */
std::string spaceComplexityBottomUp() {
    return "";
}

/** B11: Time complexity of fibIterative(n) */
std::string timeComplexityIterative() {
    return "";
}

/** B12: Space complexity of fibIterative(n) — how many variables? */
std::string spaceComplexityIterative() {
    return "";
}

// ===============================================================

#include "question3_tests.h"

int main() {
    // Part A: Code implementations
    auto h = q3_tests::newHarness();
    bool codePassed = q3_tests::addCodeTests(h,
        fibRecursive, fibMemoized, fibBottomUp, fibIterative)
        .run();   // Tip: change to .runQuick() for faster feedback

    // Part B: Analysis questions
    bool analysisPassed = q3_tests::runAnalysis();

    return (codePassed && analysisPassed) ? 0 : 1;
}
