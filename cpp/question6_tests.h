#pragma once
/**
 * Test infrastructure for Problem 3 — Coin Combination Amounts: Three Implementations.
 * Contains reference solution, benchmarks, scaling analysis, and all test cases.
 *
 * NOTE: This header must be included AFTER test_harness.h and the
 * function definitions in the .cpp file.
 */

#include <random>
#include <functional>
#include <unordered_set>

namespace q6_tests {

using SolveFn = std::function<int(int)>;

// ── Reference solution ───────────────────────────────────

inline int brute(int n) {
    std::unordered_set<int> reachable;
    reachable.insert(0);
    int coins[] = {1, 5, 10, 25};
    for (int step = 0; step < n; step++) {
        std::unordered_set<int> next(reachable);
        for (int amt : reachable) {
            for (int c : coins) {
                next.insert(amt + c);
            }
        }
        reachable = std::move(next);
    }
    return static_cast<int>(reachable.size());
}

// ── Harness builder ──────────────────────────────────────

inline harness::TestHarness<int> newHarness() {
    return harness::TestHarness<int>::forProblem(
        "Coin Combination Amounts \xe2\x80\x94 Three Implementations");
}

inline harness::TestHarness<int>& addTests(
        harness::TestHarness<int>& h,
        SolveFn solveRecursive,
        SolveFn solveMemoized,
        SolveFn solveIterative) {

    static std::mt19937 rng(42);

    return h
        // ── Correctness: Recursive (small N only, ≤5 since 4^N grows fast) ──
        .addTest("Recursive: solve(0) = 1",
            [=](){ return solveRecursive(0); }, 1)
        .addTest("Recursive: solve(1) = 5",
            [=](){ return solveRecursive(1); }, 5)
        .addTest("Recursive: solve(2) = 14",
            [=](){ return solveRecursive(2); }, 14)
        .addTest("Recursive: solve(3)",
            [=](){ return solveRecursive(3); }, brute(3))
        .addTest("Recursive: solve(5)",
            [=](){ return solveRecursive(5); }, brute(5))

        // ── Correctness: Memoized (up to moderate N) ────────
        .addTest("Memoized: solve(0) = 1",
            [=](){ return solveMemoized(0); }, 1)
        .addTest("Memoized: solve(1) = 5",
            [=](){ return solveMemoized(1); }, 5)
        .addTest("Memoized: solve(2) = 14",
            [=](){ return solveMemoized(2); }, 14)
        .addTest("Memoized: solve(5)",
            [=](){ return solveMemoized(5); }, brute(5))
        .addTest("Memoized: solve(10)",
            [=](){ return solveMemoized(10); }, brute(10))

        // ── Correctness: Iterative (up to large N) ──────────
        .addTest("Iterative: solve(0) = 1",
            [=](){ return solveIterative(0); }, 1)
        .addTest("Iterative: solve(1) = 5",
            [=](){ return solveIterative(1); }, 5)
        .addTest("Iterative: solve(2) = 14",
            [=](){ return solveIterative(2); }, 14)
        .addTest("Iterative: solve(5)",
            [=](){ return solveIterative(5); }, brute(5))
        .addTest("Iterative: solve(10)",
            [=](){ return solveIterative(10); }, brute(10))

        // ── Benchmark: all 3 at different N ─────────────────
        .addBenchmark("Recursive N=5",
            [=](){ return solveRecursive(5); })
        .addBenchmark("Memoized N=50",
            [=](){ return solveMemoized(50); })
        .addBenchmark("Iterative N=100",
            [=](){ return solveIterative(100); })

        // ── Scaling: memoized and iterative ─────────────────
        .addScaling<int>("N (memoized)",
            {10, 25, 50, 100, 200},
            std::function<int(int)>([](int n) -> int { return n; }),
            std::function<int(const int&)>(
                [=](const int& n) -> int { return solveMemoized(n); }))
        .addScaling<int>("N (iterative)",
            {10, 25, 50, 100, 200},
            std::function<int(int)>([](int n) -> int { return n; }),
            std::function<int(const int&)>(
                [=](const int& n) -> int { return solveIterative(n); }))

        // ── Random: Recursive vs Reference (small N only) ───
        .addRandomTests("Recursive vs Reference (N=0..8)", 100,
            [=]() mutable -> harness::Case<int> {
                int n = std::uniform_int_distribution<int>(0, 8)(rng);
                int expected = brute(n);
                return {
                    "N=" + std::to_string(n),
                    [=]() { return solveRecursive(n); },
                    expected
                };
            });
}

} // namespace q6_tests
