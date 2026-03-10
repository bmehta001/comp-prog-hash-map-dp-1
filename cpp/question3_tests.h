#pragma once
/**
 * Test infrastructure for Problem 2 -- Fibonacci: Four Implementations + Analysis.
 * Contains reference solution, benchmarks, scaling analysis, correctness tests,
 * and analysis question checking with feedback.
 *
 * NOTE: This header must be included AFTER test_harness.h and the
 * function definitions in the .cpp file.
 */

#include <random>
#include <functional>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

// Forward declarations for analysis functions defined in .cpp (global scope)
std::vector<int> callCountsFib5();
int totalCallsRecursive5();
int totalCallsRecursive10();
int totalCallsMemoized5();
std::string timeComplexityRecursive();
std::string spaceComplexityRecursive();
std::string timeComplexityMemoized();
std::string spaceComplexityMemoized();
std::string timeComplexityBottomUp();
std::string spaceComplexityBottomUp();
std::string timeComplexityIterative();
std::string spaceComplexityIterative();

namespace q3_tests {

using FibFn = std::function<long long(int)>;

// -- Reference solution -----------------------------------

inline long long referenceFib(int n) {
    if (n <= 1) {
        return n;
    }
    long long prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

// -- Harness builder --------------------------------------

inline harness::TestHarness<long long> newHarness() {
    return harness::TestHarness<long long>::forProblem(
        "Fibonacci \xe2\x80\x94 Four Implementations + Analysis");
}

// -- Part A: Code tests ----------------------------------

inline harness::TestHarness<long long>& addCodeTests(
        harness::TestHarness<long long>& h,
        FibFn fibRecursive,
        FibFn fibMemoized,
        FibFn fibBottomUp,
        FibFn fibIterative) {

    static std::mt19937 rng(42);

    return h
        // -- Correctness: Recursive (small N only) --------
        .addTest("Recursive: fib(0) = 0",
            [=](){ return fibRecursive(0); }, 0LL)
        .addTest("Recursive: fib(1) = 1",
            [=](){ return fibRecursive(1); }, 1LL)
        .addTest("Recursive: fib(2) = 1",
            [=](){ return fibRecursive(2); }, 1LL)
        .addTest("Recursive: fib(5) = 5",
            [=](){ return fibRecursive(5); }, 5LL)
        .addTest("Recursive: fib(10) = 55",
            [=](){ return fibRecursive(10); }, 55LL)
        .addTest("Recursive: fib(20) = 6765",
            [=](){ return fibRecursive(20); }, 6765LL)

        // -- Correctness: Memoized (up to large N) --------
        .addTest("Memoized: fib(0) = 0",
            [=](){ return fibMemoized(0); }, 0LL)
        .addTest("Memoized: fib(1) = 1",
            [=](){ return fibMemoized(1); }, 1LL)
        .addTest("Memoized: fib(2) = 1",
            [=](){ return fibMemoized(2); }, 1LL)
        .addTest("Memoized: fib(5) = 5",
            [=](){ return fibMemoized(5); }, 5LL)
        .addTest("Memoized: fib(10) = 55",
            [=](){ return fibMemoized(10); }, 55LL)
        .addTest("Memoized: fib(20) = 6765",
            [=](){ return fibMemoized(20); }, 6765LL)
        .addTest("Memoized: fib(50) = 12586269025",
            [=](){ return fibMemoized(50); }, 12586269025LL)

        // -- Correctness: Bottom-Up (up to large N) -------
        .addTest("Bottom-Up: fib(0) = 0",
            [=](){ return fibBottomUp(0); }, 0LL)
        .addTest("Bottom-Up: fib(1) = 1",
            [=](){ return fibBottomUp(1); }, 1LL)
        .addTest("Bottom-Up: fib(2) = 1",
            [=](){ return fibBottomUp(2); }, 1LL)
        .addTest("Bottom-Up: fib(5) = 5",
            [=](){ return fibBottomUp(5); }, 5LL)
        .addTest("Bottom-Up: fib(10) = 55",
            [=](){ return fibBottomUp(10); }, 55LL)
        .addTest("Bottom-Up: fib(20) = 6765",
            [=](){ return fibBottomUp(20); }, 6765LL)
        .addTest("Bottom-Up: fib(50) = 12586269025",
            [=](){ return fibBottomUp(50); }, 12586269025LL)

        // -- Correctness: Iterative (up to large N) -------
        .addTest("Iterative: fib(0) = 0",
            [=](){ return fibIterative(0); }, 0LL)
        .addTest("Iterative: fib(1) = 1",
            [=](){ return fibIterative(1); }, 1LL)
        .addTest("Iterative: fib(2) = 1",
            [=](){ return fibIterative(2); }, 1LL)
        .addTest("Iterative: fib(5) = 5",
            [=](){ return fibIterative(5); }, 5LL)
        .addTest("Iterative: fib(10) = 55",
            [=](){ return fibIterative(10); }, 55LL)
        .addTest("Iterative: fib(20) = 6765",
            [=](){ return fibIterative(20); }, 6765LL)
        .addTest("Iterative: fib(50) = 12586269025",
            [=](){ return fibIterative(50); }, 12586269025LL)

        // -- Benchmark: all 4 at N=30 ---------------------
        .addBenchmark("Recursive N=30",
            [=](){ return fibRecursive(30); })
        .addBenchmark("Memoized N=30",
            [=](){ return fibMemoized(30); })
        .addBenchmark("Bottom-Up N=30",
            [=](){ return fibBottomUp(30); })
        .addBenchmark("Iterative N=30",
            [=](){ return fibIterative(30); })

        // -- Scaling: memoized, bottom-up, and iterative --
        .addScaling<int>("N (memoized)",
            {100, 500, 1'000, 5'000, 10'000},
            std::function<int(int)>([](int n) -> int { return n; }),
            std::function<long long(const int&)>(
                [=](const int& n) -> long long { return fibMemoized(n); }))
        .addScaling<int>("N (bottom-up)",
            {100, 500, 1'000, 5'000, 10'000},
            std::function<int(int)>([](int n) -> int { return n; }),
            std::function<long long(const int&)>(
                [=](const int& n) -> long long { return fibBottomUp(n); }))
        .addScaling<int>("N (iterative)",
            {100, 500, 1'000, 5'000, 10'000},
            std::function<int(int)>([](int n) -> int { return n; }),
            std::function<long long(const int&)>(
                [=](const int& n) -> long long { return fibIterative(n); }))

        // -- Random: Recursive vs Reference ---------------
        .addRandomTests("Recursive vs Reference (N in [0, 40])", 100,
            [=]() mutable -> harness::Case<long long> {
                int n = std::uniform_int_distribution<int>(0, 40)(rng);
                long long expected = referenceFib(n);
                return {
                    "fib(" + std::to_string(n) + ")",
                    [=]() { return fibRecursive(n); },
                    expected
                };
            });
}

// -- Part B: Analysis -------------------------------------

inline std::string normalize(const std::string& s) {
    std::string result;
    for (char c : s) {
        if (!std::isspace(static_cast<unsigned char>(c))) {
            result += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
    }
    return result;
}

inline bool runAnalysis() {
    std::string border = "=======================================================";
    std::cout << "\n" << border << "\n";
    std::cout << "  Part B: Analysis Questions\n";
    std::cout << border << "\n\n";

    int total = 0, passed = 0;

    // -- B1: Call counts for fibRecursive(5) --
    total++;
    std::vector<int> counts = callCountsFib5();
    std::vector<int> expectedCounts = {3, 5, 3, 2, 1, 1};
    if (counts == expectedCounts) {
        passed++;
        std::cout << "  \xe2\x9c\x93 B1: Call counts for fibRecursive(5) \xe2\x80\x94 PASS\n\n";
        std::cout << "    Here's the full call tree you should have drawn:\n\n";
        std::cout << "      fib(5)\n";
        std::cout << "      \xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 fib(4)\n";
        std::cout << "      \xe2\x94\x82   \xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 fib(3)\n";
        std::cout << "      \xe2\x94\x82   \xe2\x94\x82   \xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 fib(2)\n";
        std::cout << "      \xe2\x94\x82   \xe2\x94\x82   \xe2\x94\x82   \xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 fib(1) = 1\n";
        std::cout << "      \xe2\x94\x82   \xe2\x94\x82   \xe2\x94\x82   \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fib(0) = 0\n";
        std::cout << "      \xe2\x94\x82   \xe2\x94\x82   \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fib(1) = 1\n";
        std::cout << "      \xe2\x94\x82   \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fib(2)\n";
        std::cout << "      \xe2\x94\x82       \xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 fib(1) = 1\n";
        std::cout << "      \xe2\x94\x82       \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fib(0) = 0\n";
        std::cout << "      \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fib(3)\n";
        std::cout << "          \xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 fib(2)\n";
        std::cout << "          \xe2\x94\x82   \xe2\x94\x9c\xe2\x94\x80\xe2\x94\x80 fib(1) = 1\n";
        std::cout << "          \xe2\x94\x82   \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fib(0) = 0\n";
        std::cout << "          \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fib(1) = 1\n\n";
        std::cout << "    Counts: fib(0)=3, fib(1)=5, fib(2)=3, fib(3)=2, fib(4)=1, fib(5)=1\n";
        std::cout << "    Notice how the counts themselves follow a Fibonacci-like pattern!\n";
    } else {
        std::cout << "  \xe2\x9c\x97 B1: Call counts for fibRecursive(5) \xe2\x80\x94 FAIL\n";
        std::cout << "    Expected: {3, 5, 3, 2, 1, 1}\n";
        std::cout << "    Got:      {";
        for (size_t i = 0; i < counts.size(); i++) {
            if (i > 0) { std::cout << ", "; }
            std::cout << counts[i];
        }
        std::cout << "}\n";
        std::cout << "    Hint: draw the full call tree on paper, starting from fib(5).\n";
    }
    std::cout << "\n";

    // -- B2: Total calls for fibRecursive(5) --
    total++;
    int tc5 = totalCallsRecursive5();
    if (tc5 == 15) {
        passed++;
        std::cout << "  \xe2\x9c\x93 B2: Total calls for fibRecursive(5) = 15 \xe2\x80\x94 PASS\n";
        std::cout << "    Sum of all nodes in the tree: 1+1+2+3+5+3 = 15\n";
    } else {
        std::cout << "  \xe2\x9c\x97 B2: Total calls for fibRecursive(5) \xe2\x80\x94 FAIL\n";
        std::cout << "    Expected: 15\n";
        std::cout << "    Got:      " << tc5 << "\n";
        std::cout << "    Hint: count every node in your call tree from B1.\n";
    }
    std::cout << "\n";

    // -- B3: Total calls for fibRecursive(10) --
    total++;
    int tc10 = totalCallsRecursive10();
    if (tc10 == 177) {
        passed++;
        std::cout << "  \xe2\x9c\x93 B3: Total calls for fibRecursive(10) = 177 \xe2\x80\x94 PASS\n";
        std::cout << "    The pattern: T(n) = 1 + T(n-1) + T(n-2)\n";
        std::cout << "    T(0)=1, T(1)=1, T(2)=3, T(3)=5, T(4)=9, T(5)=15,\n";
        std::cout << "    T(6)=25, T(7)=41, T(8)=67, T(9)=109, T(10)=177\n";
        std::cout << "    The call count itself grows exponentially!\n";
    } else {
        std::cout << "  \xe2\x9c\x97 B3: Total calls for fibRecursive(10) \xe2\x80\x94 FAIL\n";
        std::cout << "    Expected: 177\n";
        std::cout << "    Got:      " << tc10 << "\n";
        std::cout << "    Hint: T(n) = 1 + T(n-1) + T(n-2), with T(0)=1, T(1)=1.\n";
    }
    std::cout << "\n";

    // -- B4: Total calls for fibMemoized(5) --
    total++;
    int mc5 = totalCallsMemoized5();
    if (mc5 == 9) {
        passed++;
        std::cout << "  \xe2\x9c\x93 B4: Total calls for fibMemoized(5) = 9 \xe2\x80\x94 PASS\n";
        std::cout << "    With memoization, fib(5) still recurses into fib(4) and fib(3).\n";
        std::cout << "    But fib(3) was already computed during fib(4)'s recursion,\n";
        std::cout << "    so it returns from cache immediately. Only 9 calls total\n";
        std::cout << "    vs 15 without memoization. The savings grow dramatically\n";
        std::cout << "    for larger N (177 calls at N=10 drops to just 19).\n";
    } else {
        std::cout << "  \xe2\x9c\x97 B4: Total calls for fibMemoized(5) \xe2\x80\x94 FAIL\n";
        std::cout << "    Expected: 9\n";
        std::cout << "    Got:      " << mc5 << "\n";
        std::cout << "    Hint: trace through the memoized version. fib(5) calls fib(4)+fib(3).\n";
        std::cout << "    fib(4) recurses fully (computing fib(3), fib(2), fib(1), fib(0)).\n";
        std::cout << "    Then fib(3) from fib(5) hits the cache and returns immediately.\n";
    }
    std::cout << "\n";

    // -- B5-B12: Complexity Questions --
    struct CQ {
        std::string label, desc, answer, expected, feedback, hint;
    };

    CQ questions[] = {
        {"B5", "Time complexity of fibRecursive", timeComplexityRecursive(), "O(2^N)",
         "Each call branches into TWO subcalls. The call tree is a binary tree\n"
         "    of depth N, so the number of calls is roughly 2^N.\n"
         "    (More precisely, it's O(phi^N) where phi = 1.618..., the golden ratio.)",
         "Hint: look at how the call count grew from B2 to B3."},

        {"B6", "Space complexity of fibRecursive", spaceComplexityRecursive(), "O(N)",
         "Even though there are 2^N calls, they don't all exist at once.\n"
         "    The deepest path in the call tree has N frames on the stack.\n"
         "    (fib(5) -> fib(4) -> fib(3) -> fib(2) -> fib(1) = 5 frames)",
         "Hint: how deep does the call stack get? Each call waits for\n"
         "    its left child to return before calling its right child."},

        {"B7", "Time complexity of fibMemoized", timeComplexityMemoized(), "O(N)",
         "Each fib(k) for k in [0, N] is computed exactly once and cached.\n"
         "    Subsequent calls return in O(1). Total: N+1 unique computations = O(N).",
         "Hint: with memoization, how many UNIQUE fib(k) values are computed?"},

        {"B8", "Space complexity of fibMemoized", spaceComplexityMemoized(), "O(N)",
         "The memo vector has N+1 entries, and the call stack can be N deep.\n"
         "    Both are O(N), so total space is O(N).",
         "Hint: consider the memo vector size AND the call stack depth."},

        {"B9", "Time complexity of fibBottomUp", timeComplexityBottomUp(), "O(N)",
         "A single loop from 2 to N, each iteration doing O(1) work.",
         "Hint: how many iterations does the loop do?"},

        {"B10", "Space complexity of fibBottomUp", spaceComplexityBottomUp(), "O(N)",
         "The dp[] vector has N+1 entries = O(N) space.\n"
         "    No recursion, so no call stack overhead.",
         "Hint: how big is the dp[] vector?"},

        {"B11", "Time complexity of fibIterative", timeComplexityIterative(), "O(N)",
         "Same as bottom-up: one loop from 2 to N.",
         ""},

        {"B12", "Space complexity of fibIterative", spaceComplexityIterative(), "O(1)",
         "Only two variables (prev, curr) regardless of N.\n"
         "    This is the most space-efficient approach.",
         "Hint: how many variables does the loop use? Does it depend on N?"},
    };

    for (const auto& q : questions) {
        total++;
        std::string norm = normalize(q.answer);
        if (norm == q.expected) {
            passed++;
            std::cout << "  \xe2\x9c\x93 " << q.label << ": " << q.desc
                      << " = " << q.expected << " \xe2\x80\x94 PASS\n";
            if (!q.feedback.empty()) {
                std::cout << "    " << q.feedback << "\n";
            }
        } else {
            std::cout << "  \xe2\x9c\x97 " << q.label << ": " << q.desc << " \xe2\x80\x94 FAIL\n";
            std::cout << "    Got: " << q.answer << "\n";
            if (!q.hint.empty()) {
                std::cout << "    " << q.hint << "\n";
            }
        }
        std::cout << "\n";
    }

    // -- Summary --
    std::cout << border << "\n";
    std::cout << "  Analysis: " << passed << " / " << total << " questions correct\n";
    std::cout << border << "\n";

    return passed == total;
}

} // namespace q3_tests
