#pragma once
/**
 * Test infrastructure for Problem 4 — Climbing Stairs: Three Implementations.
 * Contains reference solution, benchmarks, scaling analysis, and all test cases.
 *
 * NOTE: This header must be included AFTER test_harness.h and the
 * function definitions in the .cpp file.
 */

#include <random>
#include <functional>

namespace q5_tests {

using SolveFn = std::function<long long(int)>;

// ── Reference solution ───────────────────────────────────

inline long long reference(int n) {
    if (n <= 1) {
        return 1;
    }
    long long prev = 1, curr = 2;
    for (int i = 3; i <= n; i++) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

// ── Harness builder ──────────────────────────────────────

inline harness::TestHarness<long long> newHarness() {
    return harness::TestHarness<long long>::forProblem(
        "Climbing Stairs \xe2\x80\x94 Three Implementations");
}

inline harness::TestHarness<long long>& addTests(
        harness::TestHarness<long long>& h,
        SolveFn solveRecursive,
        SolveFn solveMemoized,
        SolveFn solveIterative) {

    static std::mt19937 rng(42);

    return h
        // ── Correctness: Recursive (small N only, ≤25) ───
        .addTest("Recursive: climb(1) = 1",
            [=](){ return solveRecursive(1); }, 1LL)
        .addTest("Recursive: climb(2) = 2",
            [=](){ return solveRecursive(2); }, 2LL)
        .addTest("Recursive: climb(3) = 3",
            [=](){ return solveRecursive(3); }, 3LL)
        .addTest("Recursive: climb(5) = 8",
            [=](){ return solveRecursive(5); }, 8LL)
        .addTest("Recursive: climb(10) = 89",
            [=](){ return solveRecursive(10); }, 89LL)
        .addTest("Recursive: climb(20) = 10946",
            [=](){ return solveRecursive(20); }, 10946LL)

        // ── Correctness: Memoized (up to large N) ────────
        .addTest("Memoized: climb(1) = 1",
            [=](){ return solveMemoized(1); }, 1LL)
        .addTest("Memoized: climb(2) = 2",
            [=](){ return solveMemoized(2); }, 2LL)
        .addTest("Memoized: climb(5) = 8",
            [=](){ return solveMemoized(5); }, 8LL)
        .addTest("Memoized: climb(10) = 89",
            [=](){ return solveMemoized(10); }, 89LL)
        .addTest("Memoized: climb(20) = 10946",
            [=](){ return solveMemoized(20); }, 10946LL)
        .addTest("Memoized: climb(45) = 1836311903",
            [=](){ return solveMemoized(45); }, 1836311903LL)

        // ── Correctness: Iterative (up to large N) ───────
        .addTest("Iterative: climb(1) = 1",
            [=](){ return solveIterative(1); }, 1LL)
        .addTest("Iterative: climb(2) = 2",
            [=](){ return solveIterative(2); }, 2LL)
        .addTest("Iterative: climb(5) = 8",
            [=](){ return solveIterative(5); }, 8LL)
        .addTest("Iterative: climb(10) = 89",
            [=](){ return solveIterative(10); }, 89LL)
        .addTest("Iterative: climb(20) = 10946",
            [=](){ return solveIterative(20); }, 10946LL)
        .addTest("Iterative: climb(45) = 1836311903",
            [=](){ return solveIterative(45); }, 1836311903LL)

        // ── Benchmark: all 3 at N=30 ─────────────────────
        .addBenchmark("Recursive N=30",
            [=](){ return solveRecursive(30); })
        .addBenchmark("Memoized N=30",
            [=](){ return solveMemoized(30); })
        .addBenchmark("Iterative N=30",
            [=](){ return solveIterative(30); })

        // ── Scaling: memoized and iterative ──────────────
        .addScaling<int>("N (memoized)",
            {100, 500, 1'000, 5'000, 10'000},
            std::function<int(int)>([](int n) -> int { return n; }),
            std::function<long long(const int&)>(
                [=](const int& n) -> long long { return solveMemoized(n); }))
        .addScaling<int>("N (iterative)",
            {100, 500, 1'000, 5'000, 10'000},
            std::function<int(int)>([](int n) -> int { return n; }),
            std::function<long long(const int&)>(
                [=](const int& n) -> long long { return solveIterative(n); }))

        // ── Random: Recursive vs Reference ───────────────
        .addRandomTests("Recursive vs Reference (N=1..25)", 100,
            [=]() mutable -> harness::Case<long long> {
                int n = std::uniform_int_distribution<int>(1, 25)(rng);
                long long expected = reference(n);
                return {
                    "climb(" + std::to_string(n) + ")",
                    [=]() { return solveRecursive(n); },
                    expected
                };
            });
}

} // namespace q5_tests
