import java.util.Arrays;
import java.util.Random;
import java.util.function.Function;

/**
 * Test infrastructure for Problem 3 -- Fibonacci: Four Implementations + Analysis.
 * Contains reference solution, benchmarks, scaling, correctness tests, and
 * analysis question checking with feedback.
 */
class Question3_Tests {

    // =======================================================
    //  PART A -- Code Implementation Tests
    // =======================================================

    static TestHarness<Long> buildCodeHarness(
            Function<Integer, Long> fibRecursive,
            Function<Integer, Long> fibMemoized,
            Function<Integer, Long> fibBottomUp,
            Function<Integer, Long> fibIterative) {

        Random rng = new Random(42);

        return TestHarness.<Long>forProblem("Fibonacci \u2014 Four Implementations + Analysis")

            // -- Correctness: Recursive (small N only) --------
            .addTest("Recursive: fib(0) = 0",
                () -> fibRecursive.apply(0), 0L)
            .addTest("Recursive: fib(1) = 1",
                () -> fibRecursive.apply(1), 1L)
            .addTest("Recursive: fib(2) = 1",
                () -> fibRecursive.apply(2), 1L)
            .addTest("Recursive: fib(5) = 5",
                () -> fibRecursive.apply(5), 5L)
            .addTest("Recursive: fib(10) = 55",
                () -> fibRecursive.apply(10), 55L)
            .addTest("Recursive: fib(20) = 6765",
                () -> fibRecursive.apply(20), 6765L)

            // -- Correctness: Memoized (up to large N) --------
            .addTest("Memoized: fib(0) = 0",
                () -> fibMemoized.apply(0), 0L)
            .addTest("Memoized: fib(1) = 1",
                () -> fibMemoized.apply(1), 1L)
            .addTest("Memoized: fib(2) = 1",
                () -> fibMemoized.apply(2), 1L)
            .addTest("Memoized: fib(5) = 5",
                () -> fibMemoized.apply(5), 5L)
            .addTest("Memoized: fib(10) = 55",
                () -> fibMemoized.apply(10), 55L)
            .addTest("Memoized: fib(20) = 6765",
                () -> fibMemoized.apply(20), 6765L)
            .addTest("Memoized: fib(50) = 12586269025",
                () -> fibMemoized.apply(50), 12586269025L)

            // -- Correctness: Bottom-Up DP (up to large N) ----
            .addTest("Bottom-Up: fib(0) = 0",
                () -> fibBottomUp.apply(0), 0L)
            .addTest("Bottom-Up: fib(1) = 1",
                () -> fibBottomUp.apply(1), 1L)
            .addTest("Bottom-Up: fib(2) = 1",
                () -> fibBottomUp.apply(2), 1L)
            .addTest("Bottom-Up: fib(5) = 5",
                () -> fibBottomUp.apply(5), 5L)
            .addTest("Bottom-Up: fib(10) = 55",
                () -> fibBottomUp.apply(10), 55L)
            .addTest("Bottom-Up: fib(20) = 6765",
                () -> fibBottomUp.apply(20), 6765L)
            .addTest("Bottom-Up: fib(50) = 12586269025",
                () -> fibBottomUp.apply(50), 12586269025L)

            // -- Correctness: Iterative (up to large N) -------
            .addTest("Iterative: fib(0) = 0",
                () -> fibIterative.apply(0), 0L)
            .addTest("Iterative: fib(1) = 1",
                () -> fibIterative.apply(1), 1L)
            .addTest("Iterative: fib(2) = 1",
                () -> fibIterative.apply(2), 1L)
            .addTest("Iterative: fib(5) = 5",
                () -> fibIterative.apply(5), 5L)
            .addTest("Iterative: fib(10) = 55",
                () -> fibIterative.apply(10), 55L)
            .addTest("Iterative: fib(20) = 6765",
                () -> fibIterative.apply(20), 6765L)
            .addTest("Iterative: fib(50) = 12586269025",
                () -> fibIterative.apply(50), 12586269025L)

            // -- Benchmark: all 4 at N=30 ---------------------
            .addBenchmark("Recursive N=30",
                () -> fibRecursive.apply(30))
            .addBenchmark("Memoized N=30",
                () -> fibMemoized.apply(30))
            .addBenchmark("Bottom-Up N=30",
                () -> fibBottomUp.apply(30))
            .addBenchmark("Iterative N=30",
                () -> fibIterative.apply(30))

            // -- Scaling: memoized, bottom-up, and iterative --
            .addScaling("N (memoized)",
                new int[]{100, 500, 1_000, 5_000, 10_000},
                n -> n,
                n -> fibMemoized.apply(n))
            .addScaling("N (bottom-up)",
                new int[]{100, 500, 1_000, 5_000, 10_000},
                n -> n,
                n -> fibBottomUp.apply(n))
            .addScaling("N (iterative)",
                new int[]{100, 500, 1_000, 5_000, 10_000},
                n -> n,
                n -> fibIterative.apply(n))

            // -- Random: Recursive vs Reference ---------------
            .addRandomTests("Recursive vs Reference (N in [0, 40])", 100, () -> {
                int n = rng.nextInt(41);
                long expected = referenceFib(n);
                return new TestHarness.Case<>(
                    "fib(" + n + ")",
                    () -> fibRecursive.apply(n),
                    expected);
            });
    }

    // =======================================================
    //  PART B -- Analysis Question Checking
    // =======================================================

    static boolean runAnalysis() {
        String border = "=======================================================";
        System.out.println();
        System.out.println(border);
        System.out.println("  Part B: Analysis Questions");
        System.out.println(border);
        System.out.println();

        int total = 0;
        int passed = 0;

        // -- B1: Call counts for fibRecursive(5) --------------
        total++;
        int[] counts = Question3_Fibonacci.callCountsFib5();
        int[] expectedCounts = {3, 5, 3, 2, 1, 1};
        if (counts != null && Arrays.equals(counts, expectedCounts)) {
            passed++;
            System.out.println("  \u2713 B1: Call counts for fibRecursive(5) \u2014 PASS");
            System.out.println();
            System.out.println("    Here's the full call tree you should have drawn:");
            System.out.println();
            System.out.println("      fib(5)");
            System.out.println("      \u251C\u2500\u2500 fib(4)");
            System.out.println("      \u2502   \u251C\u2500\u2500 fib(3)");
            System.out.println("      \u2502   \u2502   \u251C\u2500\u2500 fib(2)");
            System.out.println("      \u2502   \u2502   \u2502   \u251C\u2500\u2500 fib(1) = 1");
            System.out.println("      \u2502   \u2502   \u2502   \u2514\u2500\u2500 fib(0) = 0");
            System.out.println("      \u2502   \u2502   \u2514\u2500\u2500 fib(1) = 1");
            System.out.println("      \u2502   \u2514\u2500\u2500 fib(2)");
            System.out.println("      \u2502       \u251C\u2500\u2500 fib(1) = 1");
            System.out.println("      \u2502       \u2514\u2500\u2500 fib(0) = 0");
            System.out.println("      \u2514\u2500\u2500 fib(3)");
            System.out.println("          \u251C\u2500\u2500 fib(2)");
            System.out.println("          \u2502   \u251C\u2500\u2500 fib(1) = 1");
            System.out.println("          \u2502   \u2514\u2500\u2500 fib(0) = 0");
            System.out.println("          \u2514\u2500\u2500 fib(1) = 1");
            System.out.println();
            System.out.println("    Counts: fib(0)=3, fib(1)=5, fib(2)=3, fib(3)=2, fib(4)=1, fib(5)=1");
            System.out.println("    Notice how the counts themselves follow a Fibonacci-like pattern!");
        } else {
            System.out.println("  \u2717 B1: Call counts for fibRecursive(5) \u2014 FAIL");
            System.out.println("    Expected: " + Arrays.toString(expectedCounts));
            System.out.println("    Got:      " + Arrays.toString(counts));
            System.out.println("    Hint: draw the full call tree on paper, starting from fib(5).");
        }
        System.out.println();

        // -- B2: Total calls for fibRecursive(5) -------------
        total++;
        int totalCalls5 = Question3_Fibonacci.totalCallsRecursive5();
        if (totalCalls5 == 15) {
            passed++;
            System.out.println("  \u2713 B2: Total calls for fibRecursive(5) = 15 \u2014 PASS");
            System.out.println("    Sum of all nodes in the tree: 1+1+2+3+5+3 = 15");
        } else {
            System.out.println("  \u2717 B2: Total calls for fibRecursive(5) \u2014 FAIL");
            System.out.println("    Expected: 15");
            System.out.println("    Got:      " + totalCalls5);
            System.out.println("    Hint: count every node in your call tree from B1.");
        }
        System.out.println();

        // -- B3: Total calls for fibRecursive(10) ------------
        total++;
        int totalCalls10 = Question3_Fibonacci.totalCallsRecursive10();
        if (totalCalls10 == 177) {
            passed++;
            System.out.println("  \u2713 B3: Total calls for fibRecursive(10) = 177 \u2014 PASS");
            System.out.println("    The pattern: T(n) = 1 + T(n-1) + T(n-2)");
            System.out.println("    T(0)=1, T(1)=1, T(2)=3, T(3)=5, T(4)=9, T(5)=15,");
            System.out.println("    T(6)=25, T(7)=41, T(8)=67, T(9)=109, T(10)=177");
            System.out.println("    The call count itself grows exponentially!");
        } else {
            System.out.println("  \u2717 B3: Total calls for fibRecursive(10) \u2014 FAIL");
            System.out.println("    Expected: 177");
            System.out.println("    Got:      " + totalCalls10);
            System.out.println("    Hint: T(n) = 1 + T(n-1) + T(n-2), with T(0)=1, T(1)=1.");
        }
        System.out.println();

        // -- B4: Total calls for fibMemoized(5) --------------
        total++;
        int memoCalls5 = Question3_Fibonacci.totalCallsMemoized5();
        if (memoCalls5 == 9) {
            passed++;
            System.out.println("  \u2713 B4: Total calls for fibMemoized(5) = 9 \u2014 PASS");
            System.out.println("    With memoization, fib(5) still recurses into fib(4) and fib(3).");
            System.out.println("    But fib(3) was already computed during fib(4)'s recursion,");
            System.out.println("    so it returns from cache immediately. Only 9 calls total");
            System.out.println("    vs 15 without memoization. The savings grow dramatically");
            System.out.println("    for larger N (177 calls at N=10 drops to just 19).");
        } else {
            System.out.println("  \u2717 B4: Total calls for fibMemoized(5) \u2014 FAIL");
            System.out.println("    Expected: 9");
            System.out.println("    Got:      " + memoCalls5);
            System.out.println("    Hint: trace through the memoized version. fib(5) calls fib(4)+fib(3).");
            System.out.println("    fib(4) recurses fully (computing fib(3), fib(2), fib(1), fib(0)).");
            System.out.println("    Then fib(3) from fib(5) hits the cache and returns immediately.");
        }
        System.out.println();

        // -- B5-B12: Complexity Questions ---------------------

        // B5: Time complexity of recursive
        total++;
        String tcRecursive = normalize(Question3_Fibonacci.timeComplexityRecursive());
        if (tcRecursive.equals("O(2^N)")) {
            passed++;
            System.out.println("  \u2713 B5: Time complexity of fibRecursive = O(2^N) \u2014 PASS");
            System.out.println("    Each call branches into TWO subcalls. The call tree is a binary tree");
            System.out.println("    of depth N, so the number of calls is roughly 2^N.");
            System.out.println("    (More precisely, it's O(phi^N) where phi = 1.618..., the golden ratio.)");
        } else {
            System.out.println("  \u2717 B5: Time complexity of fibRecursive \u2014 FAIL");
            System.out.println("    Got: " + Question3_Fibonacci.timeComplexityRecursive());
            System.out.println("    Hint: look at how the call count grew from B2 to B3.");
        }
        System.out.println();

        // B6: Space complexity of recursive
        total++;
        String scRecursive = normalize(Question3_Fibonacci.spaceComplexityRecursive());
        if (scRecursive.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B6: Space complexity of fibRecursive = O(N) \u2014 PASS");
            System.out.println("    Even though there are 2^N calls, they don't all exist at once.");
            System.out.println("    The deepest path in the call tree has N frames on the stack.");
            System.out.println("    (fib(5) -> fib(4) -> fib(3) -> fib(2) -> fib(1) = 5 frames)");
        } else {
            System.out.println("  \u2717 B6: Space complexity of fibRecursive \u2014 FAIL");
            System.out.println("    Got: " + Question3_Fibonacci.spaceComplexityRecursive());
            System.out.println("    Hint: how deep does the call stack get? Each call waits for");
            System.out.println("    its left child to return before calling its right child.");
        }
        System.out.println();

        // B7: Time complexity of memoized
        total++;
        String tcMemoized = normalize(Question3_Fibonacci.timeComplexityMemoized());
        if (tcMemoized.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B7: Time complexity of fibMemoized = O(N) \u2014 PASS");
            System.out.println("    Each fib(k) for k in [0, N] is computed exactly once and cached.");
            System.out.println("    Subsequent calls return in O(1). Total: N+1 unique computations = O(N).");
        } else {
            System.out.println("  \u2717 B7: Time complexity of fibMemoized \u2014 FAIL");
            System.out.println("    Got: " + Question3_Fibonacci.timeComplexityMemoized());
            System.out.println("    Hint: with memoization, how many UNIQUE fib(k) values are computed?");
        }
        System.out.println();

        // B8: Space complexity of memoized
        total++;
        String scMemoized = normalize(Question3_Fibonacci.spaceComplexityMemoized());
        if (scMemoized.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B8: Space complexity of fibMemoized = O(N) \u2014 PASS");
            System.out.println("    The memo array has N+1 entries, and the call stack can be N deep.");
            System.out.println("    Both are O(N), so total space is O(N).");
        } else {
            System.out.println("  \u2717 B8: Space complexity of fibMemoized \u2014 FAIL");
            System.out.println("    Got: " + Question3_Fibonacci.spaceComplexityMemoized());
            System.out.println("    Hint: consider the memo array size AND the call stack depth.");
        }
        System.out.println();

        // B9: Time complexity of bottom-up
        total++;
        String tcBottomUp = normalize(Question3_Fibonacci.timeComplexityBottomUp());
        if (tcBottomUp.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B9: Time complexity of fibBottomUp = O(N) \u2014 PASS");
            System.out.println("    A single loop from 2 to N, each iteration doing O(1) work.");
        } else {
            System.out.println("  \u2717 B9: Time complexity of fibBottomUp \u2014 FAIL");
            System.out.println("    Got: " + Question3_Fibonacci.timeComplexityBottomUp());
            System.out.println("    Hint: how many iterations does the loop do?");
        }
        System.out.println();

        // B10: Space complexity of bottom-up
        total++;
        String scBottomUp = normalize(Question3_Fibonacci.spaceComplexityBottomUp());
        if (scBottomUp.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B10: Space complexity of fibBottomUp = O(N) \u2014 PASS");
            System.out.println("    The dp[] array has N+1 entries = O(N) space.");
            System.out.println("    No recursion, so no call stack overhead.");
        } else {
            System.out.println("  \u2717 B10: Space complexity of fibBottomUp \u2014 FAIL");
            System.out.println("    Got: " + Question3_Fibonacci.spaceComplexityBottomUp());
            System.out.println("    Hint: how big is the dp[] array?");
        }
        System.out.println();

        // B11: Time complexity of iterative
        total++;
        String tcIterative = normalize(Question3_Fibonacci.timeComplexityIterative());
        if (tcIterative.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B11: Time complexity of fibIterative = O(N) \u2014 PASS");
            System.out.println("    Same as bottom-up: one loop from 2 to N.");
        } else {
            System.out.println("  \u2717 B11: Time complexity of fibIterative \u2014 FAIL");
            System.out.println("    Got: " + Question3_Fibonacci.timeComplexityIterative());
        }
        System.out.println();

        // B12: Space complexity of iterative
        total++;
        String scIterative = normalize(Question3_Fibonacci.spaceComplexityIterative());
        if (scIterative.equals("O(1)")) {
            passed++;
            System.out.println("  \u2713 B12: Space complexity of fibIterative = O(1) \u2014 PASS");
            System.out.println("    Only two variables (prev, curr) regardless of N.");
            System.out.println("    This is the most space-efficient approach.");
        } else {
            System.out.println("  \u2717 B12: Space complexity of fibIterative \u2014 FAIL");
            System.out.println("    Got: " + Question3_Fibonacci.spaceComplexityIterative());
            System.out.println("    Hint: how many variables does the loop use? Does it depend on N?");
        }
        System.out.println();

        // -- Summary ------------------------------------------
        System.out.println(border);
        System.out.printf("  Analysis: %d / %d questions correct%n", passed, total);
        System.out.println(border);

        return passed == total;
    }

    // -- Helpers ----------------------------------------------

    private static long referenceFib(int n) {
        if (n <= 1) {
            return n;
        }
        long prev = 0, curr = 1;
        for (int i = 2; i <= n; i++) {
            long next = prev + curr;
            prev = curr;
            curr = next;
        }
        return curr;
    }

    /** Normalize complexity strings: trim, uppercase, remove spaces. */
    private static String normalize(String s) {
        if (s == null) {
            return "";
        }
        return s.trim().toUpperCase().replaceAll("\\s+", "");
    }
}
