/**
 * ===============================================================
 *  PROBLEM 4 — Factorial: Four Implementations + Analysis
 * ===============================================================
 *
 *  The factorial function is defined as:
 *    n! = n × (n-1) × ... × 1
 *    0! = 1
 *
 *  First few values: 1, 1, 2, 6, 24, 120, 720, 5040, ...
 *
 *  ===============================================================
 *   PART A — Code Implementations
 *  ===============================================================
 *
 *  Implement FOUR different approaches to compute n!:
 *
 *  --- Approach 1: Naive Recursive --------------------------------
 *  Direct translation of the recurrence relation.
 *  Base case: 0! = 1
 *  Recursive case: n! = n * (n-1)!
 *
 *  --- Approach 2: Memoized (Top-Down DP) -------------------------
 *  Same recursive structure, but cache results in a
 *  std::vector<long long> or a plain array.
 *  Before computing n!, check if it's already been computed.
 *
 *  --- Approach 3: Bottom-Up DP (Array) ---------------------------
 *  Build the answer from 0! up to n! using a dp vector/array.
 *  Fill dp[0] = 1, then dp[i] = i * dp[i-1] for i >= 1.
 *
 *  --- Approach 4: Iterative (Accumulator) ------------------------
 *  Same bottom-up idea, but instead of storing the whole array,
 *  keep only a single running product.
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
 *  Key educational point: Unlike Fibonacci, factorial has NO
 *  overlapping subproblems. Each fact(k) is called exactly once,
 *  so memoization adds overhead with no benefit.
 *
 *  Compile & run:
 *    g++ -std=c++17 -O2 question4_factorial.cpp -o q4 && ./q4
 *    cl /std:c++17 /EHsc /O2 question4_factorial.cpp /Fe:q4.exe && q4.exe
 * ===============================================================
 */

#include "test_harness.h"
#include <vector>
#include <string>
#include <functional>

// ===============================================================
//  PART A — Code Implementations
// ===============================================================

long long factRecursive(int n) {
    // TODO: Implement naive recursive factorial
    // Base case: 0! = 1 (also 1! = 1)
    // Recursive case: n! = n * (n-1)!
    return -1;
}

long long factMemoized(int n) {
    // TODO: Implement memoized (top-down DP) factorial
    // Create a std::vector<long long> memo of size n+1, initialized to -1
    // Use a helper function that checks memo[k] before computing
    // If memo[k] != -1, return it; otherwise compute, store, return
    return -1;
}

long long factBottomUp(int n) {
    // TODO: Implement bottom-up DP factorial with an array
    // Create a std::vector<long long> dp of size n+1
    // Set dp[0] = 1
    // Fill dp[i] = i * dp[i-1] for i from 1 to n
    // Return dp[n]
    return -1;
}

long long factIterative(int n) {
    // TODO: Implement iterative factorial with an accumulator
    // Use one variable: result = 1
    // Loop from 2 to n, multiplying: result *= i
    // No array needed — just one running product
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
 * B1: When factRecursive(5) runs, how many times is each fact(k) called?
 *
 * Return a vector of length 6 where index k = number of times fact(k)
 * is called. For example, if fact(3) is called 2 times, vec[3] = 2.
 *
 * Hint: trace the call chain starting from fact(5).
 * fact(5) calls fact(4), which calls fact(3), which calls fact(2),
 * which calls fact(1), which calls fact(0). It's a straight line!
 * Unlike Fibonacci, there is NO branching.
 */
std::vector<int> callCountsFactorial5() {
    // TODO: Fill in the call counts for fact(0) through fact(5)
    //       vec[0] = times fact(0) is called
    //       vec[1] = times fact(1) is called
    //       ...
    //       vec[5] = times fact(5) is called
    return {0, 0, 0, 0, 0, 0};
}

/**
 * B2: What is the TOTAL number of function calls made by factRecursive(5)?
 * Count every call, including the initial call to fact(5) itself.
 */
int totalCallsRecursive5() {
    return 0;
}

/**
 * B3: What is the TOTAL number of function calls made by factRecursive(10)?
 * You don't need to draw a tree — the call chain is linear.
 *
 * Hint: Let T(n) = total calls for factRecursive(n).
 * T(0) = 1. What is T(n) in terms of T(n-1)?
 */
int totalCallsRecursive10() {
    return 0;
}

/**
 * B4: What is the TOTAL number of function calls made by factMemoized(5)?
 * With memoization, each fact(k) is computed at most once.
 * But factorial already calls each fact(k) exactly once!
 *
 * Hint: trace through the memoized version. Since there are no
 * overlapping subproblems, the memo cache is never hit.
 * How does this compare to the non-memoized version?
 */
int totalCallsMemoized5() {
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

/** B5: Time complexity of factRecursive(n) */
std::string timeComplexityRecursive() {
    return "";
}

/** B6: Space complexity of factRecursive(n) — think about call stack depth */
std::string spaceComplexityRecursive() {
    return "";
}

/** B7: Time complexity of factMemoized(n) */
std::string timeComplexityMemoized() {
    return "";
}

/** B8: Space complexity of factMemoized(n) — memo vector + call stack */
std::string spaceComplexityMemoized() {
    return "";
}

/** B9: Time complexity of factBottomUp(n) */
std::string timeComplexityBottomUp() {
    return "";
}

/** B10: Space complexity of factBottomUp(n) — the dp[] vector */
std::string spaceComplexityBottomUp() {
    return "";
}

/** B11: Time complexity of factIterative(n) */
std::string timeComplexityIterative() {
    return "";
}

/** B12: Space complexity of factIterative(n) — how many variables? */
std::string spaceComplexityIterative() {
    return "";
}

// ===============================================================

#include "question4_tests.h"

int main() {
    // Part A: Code implementations
    auto h = q4_tests::newHarness();
    bool codePassed = q4_tests::addCodeTests(h,
        factRecursive, factMemoized, factBottomUp, factIterative)
        .run();

    // Part B: Analysis questions
    bool analysisPassed = q4_tests::runAnalysis();

    return (codePassed && analysisPassed) ? 0 : 1;
}
