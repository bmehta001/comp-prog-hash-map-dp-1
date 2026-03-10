#pragma once
/**
 * Test infrastructure for Problem 4 — Factorial: Four Implementations + Analysis.
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
std::vector<int> callCountsFactorial5();
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

namespace q4_tests {

using FactFn = std::function<long long(int)>;

// ── Reference solution ───────────────────────────────────

inline long long referenceFact(int n) {
    long long result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

// ── Harness builder ──────────────────────────────────────

inline harness::TestHarness<long long> newHarness() {
    return harness::TestHarness<long long>::forProblem(
        "Factorial \xe2\x80\x94 Four Implementations + Analysis");
}

// ── Part A: Code tests ──────────────────────────────────

inline harness::TestHarness<long long>& addCodeTests(
        harness::TestHarness<long long>& h,
        FactFn factRecursive,
        FactFn factMemoized,
        FactFn factBottomUp,
        FactFn factIterative) {

    static std::mt19937 rng(42);

    return h
        // ── Correctness: Recursive ──────────────────────
        .addTest("Recursive: fact(0) = 1",
            [=](){ return factRecursive(0); }, 1LL)
        .addTest("Recursive: fact(1) = 1",
            [=](){ return factRecursive(1); }, 1LL)
        .addTest("Recursive: fact(2) = 2",
            [=](){ return factRecursive(2); }, 2LL)
        .addTest("Recursive: fact(5) = 120",
            [=](){ return factRecursive(5); }, 120LL)
        .addTest("Recursive: fact(10) = 3628800",
            [=](){ return factRecursive(10); }, 3628800LL)
        .addTest("Recursive: fact(15) = 1307674368000",
            [=](){ return factRecursive(15); }, 1307674368000LL)
        .addTest("Recursive: fact(20) = 2432902008176640000",
            [=](){ return factRecursive(20); }, 2432902008176640000LL)

        // ── Correctness: Memoized ───────────────────────
        .addTest("Memoized: fact(0) = 1",
            [=](){ return factMemoized(0); }, 1LL)
        .addTest("Memoized: fact(1) = 1",
            [=](){ return factMemoized(1); }, 1LL)
        .addTest("Memoized: fact(2) = 2",
            [=](){ return factMemoized(2); }, 2LL)
        .addTest("Memoized: fact(5) = 120",
            [=](){ return factMemoized(5); }, 120LL)
        .addTest("Memoized: fact(10) = 3628800",
            [=](){ return factMemoized(10); }, 3628800LL)
        .addTest("Memoized: fact(15) = 1307674368000",
            [=](){ return factMemoized(15); }, 1307674368000LL)
        .addTest("Memoized: fact(20) = 2432902008176640000",
            [=](){ return factMemoized(20); }, 2432902008176640000LL)

        // ── Correctness: Bottom-Up ──────────────────────
        .addTest("Bottom-Up: fact(0) = 1",
            [=](){ return factBottomUp(0); }, 1LL)
        .addTest("Bottom-Up: fact(1) = 1",
            [=](){ return factBottomUp(1); }, 1LL)
        .addTest("Bottom-Up: fact(2) = 2",
            [=](){ return factBottomUp(2); }, 2LL)
        .addTest("Bottom-Up: fact(5) = 120",
            [=](){ return factBottomUp(5); }, 120LL)
        .addTest("Bottom-Up: fact(10) = 3628800",
            [=](){ return factBottomUp(10); }, 3628800LL)
        .addTest("Bottom-Up: fact(15) = 1307674368000",
            [=](){ return factBottomUp(15); }, 1307674368000LL)
        .addTest("Bottom-Up: fact(20) = 2432902008176640000",
            [=](){ return factBottomUp(20); }, 2432902008176640000LL)

        // ── Correctness: Iterative ──────────────────────
        .addTest("Iterative: fact(0) = 1",
            [=](){ return factIterative(0); }, 1LL)
        .addTest("Iterative: fact(1) = 1",
            [=](){ return factIterative(1); }, 1LL)
        .addTest("Iterative: fact(2) = 2",
            [=](){ return factIterative(2); }, 2LL)
        .addTest("Iterative: fact(5) = 120",
            [=](){ return factIterative(5); }, 120LL)
        .addTest("Iterative: fact(10) = 3628800",
            [=](){ return factIterative(10); }, 3628800LL)
        .addTest("Iterative: fact(15) = 1307674368000",
            [=](){ return factIterative(15); }, 1307674368000LL)
        .addTest("Iterative: fact(20) = 2432902008176640000",
            [=](){ return factIterative(20); }, 2432902008176640000LL)

        // ── Benchmark: all 4 at N=20 ────────────────────
        .addBenchmark("Recursive N=20",
            [=](){ return factRecursive(20); })
        .addBenchmark("Memoized N=20",
            [=](){ return factMemoized(20); })
        .addBenchmark("Bottom-Up N=20",
            [=](){ return factBottomUp(20); })
        .addBenchmark("Iterative N=20",
            [=](){ return factIterative(20); })

        // ── Scaling: all 4 approaches ───────────────────
        .addScaling<int>("N (recursive)",
            {100, 500, 1'000, 5'000, 10'000},
            std::function<int(int)>([](int n) -> int { return n; }),
            std::function<long long(const int&)>(
                [=](const int& n) -> long long { return factRecursive(n); }))
        .addScaling<int>("N (memoized)",
            {100, 500, 1'000, 5'000, 10'000},
            std::function<int(int)>([](int n) -> int { return n; }),
            std::function<long long(const int&)>(
                [=](const int& n) -> long long { return factMemoized(n); }))
        .addScaling<int>("N (bottom-up)",
            {100, 500, 1'000, 5'000, 10'000},
            std::function<int(int)>([](int n) -> int { return n; }),
            std::function<long long(const int&)>(
                [=](const int& n) -> long long { return factBottomUp(n); }))
        .addScaling<int>("N (iterative)",
            {100, 500, 1'000, 5'000, 10'000},
            std::function<int(int)>([](int n) -> int { return n; }),
            std::function<long long(const int&)>(
                [=](const int& n) -> long long { return factIterative(n); }))

        // ── Random: Recursive vs Reference ──────────────
        .addRandomTests("Recursive vs Reference (N in [0, 20])", 100,
            [=]() mutable -> harness::Case<long long> {
                int n = std::uniform_int_distribution<int>(0, 20)(rng);
                long long expected = referenceFact(n);
                return {
                    "fact(" + std::to_string(n) + ")",
                    [=]() { return factRecursive(n); },
                    expected
                };
            });
}

// ── Part B: Analysis ─────────────────────────────────────

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

    // -- B1: Call counts for factRecursive(5) --
    total++;
    std::vector<int> counts = callCountsFactorial5();
    std::vector<int> expectedCounts = {1, 1, 1, 1, 1, 1};
    if (counts == expectedCounts) {
        passed++;
        std::cout << "  \xe2\x9c\x93 B1: Call counts for factRecursive(5) \xe2\x80\x94 PASS\n\n";
        std::cout << "    Here's the linear call chain you should have traced:\n\n";
        std::cout << "      fact(5)\n";
        std::cout << "      \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fact(4)\n";
        std::cout << "          \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fact(3)\n";
        std::cout << "              \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fact(2)\n";
        std::cout << "                  \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fact(1)\n";
        std::cout << "                      \xe2\x94\x94\xe2\x94\x80\xe2\x94\x80 fact(0) = 1\n\n";
        std::cout << "    Each fact(k) is called exactly once \xe2\x80\x94 a straight line!\n";
        std::cout << "    Unlike Fibonacci's branching tree, factorial has NO\n";
        std::cout << "    overlapping subproblems.\n";
    } else {
        std::cout << "  \xe2\x9c\x97 B1: Call counts for factRecursive(5) \xe2\x80\x94 FAIL\n";
        std::cout << "    Expected: {1, 1, 1, 1, 1, 1}\n";
        std::cout << "    Got:      {";
        for (size_t i = 0; i < counts.size(); i++) {
            if (i > 0) { std::cout << ", "; }
            std::cout << counts[i];
        }
        std::cout << "}\n";
        std::cout << "    Hint: trace the call chain from fact(5). It's a straight\n";
        std::cout << "    line \xe2\x80\x94 each fact(k) calls fact(k-1) exactly once.\n";
    }
    std::cout << "\n";

    // -- B2: Total calls for factRecursive(5) --
    total++;
    int tc5 = totalCallsRecursive5();
    if (tc5 == 6) {
        passed++;
        std::cout << "  \xe2\x9c\x93 B2: Total calls for factRecursive(5) = 6 \xe2\x80\x94 PASS\n";
        std::cout << "    fact(5) -> fact(4) -> fact(3) -> fact(2) -> fact(1) -> fact(0)\n";
        std::cout << "    That's 6 calls total: one for each value from 5 down to 0.\n";
    } else {
        std::cout << "  \xe2\x9c\x97 B2: Total calls for factRecursive(5) \xe2\x80\x94 FAIL\n";
        std::cout << "    Expected: 6\n";
        std::cout << "    Got:      " << tc5 << "\n";
        std::cout << "    Hint: count every node in the call chain from B1.\n";
    }
    std::cout << "\n";

    // -- B3: Total calls for factRecursive(10) --
    total++;
    int tc10 = totalCallsRecursive10();
    if (tc10 == 11) {
        passed++;
        std::cout << "  \xe2\x9c\x93 B3: Total calls for factRecursive(10) = 11 \xe2\x80\x94 PASS\n";
        std::cout << "    The pattern: T(n) = n + 1\n";
        std::cout << "    T(0)=1, T(1)=2, T(2)=3, ..., T(10)=11\n";
        std::cout << "    The call count grows linearly, not exponentially!\n";
    } else {
        std::cout << "  \xe2\x9c\x97 B3: Total calls for factRecursive(10) \xe2\x80\x94 FAIL\n";
        std::cout << "    Expected: 11\n";
        std::cout << "    Got:      " << tc10 << "\n";
        std::cout << "    Hint: T(n) = 1 + T(n-1), with T(0)=1. What is T(10)?\n";
    }
    std::cout << "\n";

    // -- B4: Total calls for factMemoized(5) --
    total++;
    int mc5 = totalCallsMemoized5();
    if (mc5 == 6) {
        passed++;
        std::cout << "  \xe2\x9c\x93 B4: Total calls for factMemoized(5) = 6 \xe2\x80\x94 PASS\n";
        std::cout << "    6 calls \xe2\x80\x94 exactly the same as without memoization!\n";
        std::cout << "    Memoization adds overhead with no benefit.\n";
    } else {
        std::cout << "  \xe2\x9c\x97 B4: Total calls for factMemoized(5) \xe2\x80\x94 FAIL\n";
        std::cout << "    Expected: 6\n";
        std::cout << "    Got:      " << mc5 << "\n";
        std::cout << "    Hint: since there are no overlapping subproblems,\n";
        std::cout << "    the memo cache is never hit. Same count as recursive!\n";
    }
    std::cout << "\n";

    // -- B5-B12: Complexity Questions --
    struct CQ {
        std::string label, desc, answer, expected, feedback, hint;
    };

    CQ questions[] = {
        {"B5", "Time complexity of factRecursive", timeComplexityRecursive(), "O(N)",
         "Each call does O(1) work and makes exactly one recursive call.\n"
         "    The chain has N+1 calls total, so time is O(N).\n"
         "    Unlike Fibonacci, there is no branching \xe2\x80\x94 no exponential blowup!",
         "Hint: how many calls are in the chain? Each does O(1) work."},

        {"B6", "Space complexity of factRecursive", spaceComplexityRecursive(), "O(N)",
         "The call stack grows N+1 frames deep:\n"
         "    fact(5) -> fact(4) -> fact(3) -> fact(2) -> fact(1) -> fact(0)\n"
         "    Each frame waits for the next to return.",
         "Hint: how deep does the call stack get?"},

        {"B7", "Time complexity of factMemoized", timeComplexityMemoized(), "O(N)",
         "Same as recursive \xe2\x80\x94 each fact(k) is computed once, O(N) total.\n"
         "    Memoization doesn't help here because there are no overlapping subproblems.",
         "Hint: does memoization reduce the number of calls for factorial?"},

        {"B8", "Space complexity of factMemoized", spaceComplexityMemoized(), "O(N)",
         "The memo vector has N+1 entries, and the call stack is N deep.\n"
         "    Both are O(N), so total space is O(N).",
         "Hint: consider the memo vector size AND the call stack depth."},

        {"B9", "Time complexity of factBottomUp", timeComplexityBottomUp(), "O(N)",
         "A single loop from 1 to N, each iteration doing O(1) work.",
         "Hint: how many iterations does the loop do?"},

        {"B10", "Space complexity of factBottomUp", spaceComplexityBottomUp(), "O(N)",
         "The dp[] vector has N+1 entries = O(N) space.\n"
         "    No recursion, so no call stack overhead.",
         "Hint: how big is the dp[] vector?"},

        {"B11", "Time complexity of factIterative", timeComplexityIterative(), "O(N)",
         "Same as bottom-up: one loop from 1 to N.",
         ""},

        {"B12", "Space complexity of factIterative", spaceComplexityIterative(), "O(1)",
         "Only one variable (result) regardless of N.\n"
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

} // namespace q4_tests
