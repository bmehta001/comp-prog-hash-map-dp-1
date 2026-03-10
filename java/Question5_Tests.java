import java.util.Random;
import java.util.function.Function;

/**
 * Test infrastructure for Problem 5 -- Climbing Stairs: Three Implementations.
 * Contains reference solution, benchmarks, scaling analysis, and all test cases.
 */
class Question5_Tests {

    static TestHarness<Long> buildHarness(
            Function<Integer, Long> solveRecursive,
            Function<Integer, Long> solveMemoized,
            Function<Integer, Long> solveIterative) {

        Random rng = new Random(42);

        return TestHarness.<Long>forProblem("Climbing Stairs \u2014 Three Implementations")

            // -- Correctness: Recursive (small N only, <=25) ---
            .addTest("Recursive: climb(1) = 1",
                () -> solveRecursive.apply(1), 1L)
            .addTest("Recursive: climb(2) = 2",
                () -> solveRecursive.apply(2), 2L)
            .addTest("Recursive: climb(3) = 3",
                () -> solveRecursive.apply(3), 3L)
            .addTest("Recursive: climb(5) = 8",
                () -> solveRecursive.apply(5), 8L)
            .addTest("Recursive: climb(10) = 89",
                () -> solveRecursive.apply(10), 89L)
            .addTest("Recursive: climb(20) = 10946",
                () -> solveRecursive.apply(20), 10946L)

            // -- Correctness: Memoized (up to large N) --------
            .addTest("Memoized: climb(1) = 1",
                () -> solveMemoized.apply(1), 1L)
            .addTest("Memoized: climb(2) = 2",
                () -> solveMemoized.apply(2), 2L)
            .addTest("Memoized: climb(5) = 8",
                () -> solveMemoized.apply(5), 8L)
            .addTest("Memoized: climb(10) = 89",
                () -> solveMemoized.apply(10), 89L)
            .addTest("Memoized: climb(20) = 10946",
                () -> solveMemoized.apply(20), 10946L)
            .addTest("Memoized: climb(45) = 1836311903",
                () -> solveMemoized.apply(45), 1836311903L)

            // -- Correctness: Iterative (up to large N) -------
            .addTest("Iterative: climb(1) = 1",
                () -> solveIterative.apply(1), 1L)
            .addTest("Iterative: climb(2) = 2",
                () -> solveIterative.apply(2), 2L)
            .addTest("Iterative: climb(5) = 8",
                () -> solveIterative.apply(5), 8L)
            .addTest("Iterative: climb(10) = 89",
                () -> solveIterative.apply(10), 89L)
            .addTest("Iterative: climb(20) = 10946",
                () -> solveIterative.apply(20), 10946L)
            .addTest("Iterative: climb(45) = 1836311903",
                () -> solveIterative.apply(45), 1836311903L)

            // -- Benchmark: all 3 at N=30 ---------------------
            .addBenchmark("Recursive N=30",
                () -> solveRecursive.apply(30))
            .addBenchmark("Memoized N=30",
                () -> solveMemoized.apply(30))
            .addBenchmark("Iterative N=30",
                () -> solveIterative.apply(30))

            // -- Scaling: memoized and iterative --------------
            .addScaling("N (memoized)",
                new int[]{100, 500, 1_000, 5_000, 10_000},
                n -> n,
                n -> solveMemoized.apply(n))
            .addScaling("N (iterative)",
                new int[]{100, 500, 1_000, 5_000, 10_000},
                n -> n,
                n -> solveIterative.apply(n))

            // -- Random: Recursive vs Reference ---------------
            .addRandomTests("Recursive vs Reference (N=1..25)", 100, () -> {
                int n = rng.nextInt(25) + 1;
                long expected = reference(n);
                return new TestHarness.Case<>(
                    "climb(" + n + ")",
                    () -> solveRecursive.apply(n),
                    expected);
            });
    }

    // -- Reference solution -----------------------------------

    private static long reference(int n) {
        if (n <= 1) {
            return 1;
        }
        long prev = 1, curr = 2;
        for (int i = 3; i <= n; i++) {
            long next = prev + curr;
            prev = curr;
            curr = next;
        }
        return curr;
    }
}
