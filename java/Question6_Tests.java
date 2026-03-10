import java.util.*;
import java.util.function.*;

/**
 * Test infrastructure for Problem 6 — Coin Combination Amounts: Three Implementations.
 * Contains reference solution, benchmarks, scaling analysis, and all test cases.
 */
class Question6_Tests {

    static TestHarness<Integer> buildHarness(
            Function<Integer, Integer> solveRecursive,
            Function<Integer, Integer> solveMemoized,
            Function<Integer, Integer> solveIterative) {

        Random rng = new Random(42);

        return TestHarness.<Integer>forProblem("Coin Combination Amounts \u2014 Three Implementations")

            // ── Correctness: Recursive (small N only, ≤5 since 4^N grows fast) ──
            .addTest("Recursive: solve(0) = 1",
                () -> solveRecursive.apply(0), 1)
            .addTest("Recursive: solve(1) = 5",
                () -> solveRecursive.apply(1), 5)
            .addTest("Recursive: solve(2) = 14",
                () -> solveRecursive.apply(2), 14)
            .addTest("Recursive: solve(3)",
                () -> solveRecursive.apply(3), brute(3))
            .addTest("Recursive: solve(5)",
                () -> solveRecursive.apply(5), brute(5))

            // ── Correctness: Memoized (up to moderate N) ────────
            .addTest("Memoized: solve(0) = 1",
                () -> solveMemoized.apply(0), 1)
            .addTest("Memoized: solve(1) = 5",
                () -> solveMemoized.apply(1), 5)
            .addTest("Memoized: solve(2) = 14",
                () -> solveMemoized.apply(2), 14)
            .addTest("Memoized: solve(5)",
                () -> solveMemoized.apply(5), brute(5))
            .addTest("Memoized: solve(10)",
                () -> solveMemoized.apply(10), brute(10))

            // ── Correctness: Iterative (up to large N) ──────────
            .addTest("Iterative: solve(0) = 1",
                () -> solveIterative.apply(0), 1)
            .addTest("Iterative: solve(1) = 5",
                () -> solveIterative.apply(1), 5)
            .addTest("Iterative: solve(2) = 14",
                () -> solveIterative.apply(2), 14)
            .addTest("Iterative: solve(5)",
                () -> solveIterative.apply(5), brute(5))
            .addTest("Iterative: solve(10)",
                () -> solveIterative.apply(10), brute(10))

            // ── Benchmark: all 3 at different N ─────────────────
            .addBenchmark("Recursive N=5",
                () -> solveRecursive.apply(5))
            .addBenchmark("Memoized N=50",
                () -> solveMemoized.apply(50))
            .addBenchmark("Iterative N=100",
                () -> solveIterative.apply(100))

            // ── Scaling: memoized and iterative ─────────────────
            .addScaling("N (memoized)",
                new int[]{10, 25, 50, 100, 200},
                n -> n,
                n -> solveMemoized.apply(n))
            .addScaling("N (iterative)",
                new int[]{10, 25, 50, 100, 200},
                n -> n,
                n -> solveIterative.apply(n))

            // ── Random: Recursive vs Reference (small N only) ───
            .addRandomTests("Recursive vs Reference (N=0..8)", 100, () -> {
                int n = rng.nextInt(9);
                int expected = brute(n);
                return new TestHarness.Case<>(
                    "N=" + n,
                    () -> solveRecursive.apply(n),
                    expected);
            });
    }

    // ── Reference solution ───────────────────────────────────

    private static int brute(int n) {
        Set<Integer> reachable = new HashSet<>();
        reachable.add(0);
        int[] coins = {1, 5, 10, 25};
        for (int step = 0; step < n; step++) {
            Set<Integer> next = new HashSet<>(reachable);
            for (int amt : reachable) {
                for (int c : coins) {
                    next.add(amt + c);
                }
            }
            reachable = next;
        }
        return reachable.size();
    }
}
