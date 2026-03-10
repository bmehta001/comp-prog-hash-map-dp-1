import java.util.Arrays;
import java.util.Random;
import java.util.function.Function;

/**
 * Test infrastructure for Problem 4 -- Factorial: Four Implementations + Analysis.
 * Contains reference solution, benchmarks, scaling, correctness tests, and
 * analysis question checking with feedback.
 */
class Question4_Tests {

    // =======================================================
    //  PART A -- Code Implementation Tests
    // =======================================================

    static TestHarness<Long> buildCodeHarness(
            Function<Integer, Long> factRecursive,
            Function<Integer, Long> factMemoized,
            Function<Integer, Long> factBottomUp,
            Function<Integer, Long> factIterative) {

        Random rng = new Random(42);

        return TestHarness.<Long>forProblem("Factorial \u2014 Four Implementations + Analysis")

            // -- Correctness: Recursive -----------------------
            .addTest("Recursive: fact(0) = 1",
                () -> factRecursive.apply(0), 1L)
            .addTest("Recursive: fact(1) = 1",
                () -> factRecursive.apply(1), 1L)
            .addTest("Recursive: fact(2) = 2",
                () -> factRecursive.apply(2), 2L)
            .addTest("Recursive: fact(5) = 120",
                () -> factRecursive.apply(5), 120L)
            .addTest("Recursive: fact(10) = 3628800",
                () -> factRecursive.apply(10), 3628800L)
            .addTest("Recursive: fact(15) = 1307674368000",
                () -> factRecursive.apply(15), 1307674368000L)
            .addTest("Recursive: fact(20) = 2432902008176640000",
                () -> factRecursive.apply(20), 2432902008176640000L)

            // -- Correctness: Memoized ------------------------
            .addTest("Memoized: fact(0) = 1",
                () -> factMemoized.apply(0), 1L)
            .addTest("Memoized: fact(1) = 1",
                () -> factMemoized.apply(1), 1L)
            .addTest("Memoized: fact(2) = 2",
                () -> factMemoized.apply(2), 2L)
            .addTest("Memoized: fact(5) = 120",
                () -> factMemoized.apply(5), 120L)
            .addTest("Memoized: fact(10) = 3628800",
                () -> factMemoized.apply(10), 3628800L)
            .addTest("Memoized: fact(15) = 1307674368000",
                () -> factMemoized.apply(15), 1307674368000L)
            .addTest("Memoized: fact(20) = 2432902008176640000",
                () -> factMemoized.apply(20), 2432902008176640000L)

            // -- Correctness: Bottom-Up DP --------------------
            .addTest("Bottom-Up: fact(0) = 1",
                () -> factBottomUp.apply(0), 1L)
            .addTest("Bottom-Up: fact(1) = 1",
                () -> factBottomUp.apply(1), 1L)
            .addTest("Bottom-Up: fact(2) = 2",
                () -> factBottomUp.apply(2), 2L)
            .addTest("Bottom-Up: fact(5) = 120",
                () -> factBottomUp.apply(5), 120L)
            .addTest("Bottom-Up: fact(10) = 3628800",
                () -> factBottomUp.apply(10), 3628800L)
            .addTest("Bottom-Up: fact(15) = 1307674368000",
                () -> factBottomUp.apply(15), 1307674368000L)
            .addTest("Bottom-Up: fact(20) = 2432902008176640000",
                () -> factBottomUp.apply(20), 2432902008176640000L)

            // -- Correctness: Iterative -----------------------
            .addTest("Iterative: fact(0) = 1",
                () -> factIterative.apply(0), 1L)
            .addTest("Iterative: fact(1) = 1",
                () -> factIterative.apply(1), 1L)
            .addTest("Iterative: fact(2) = 2",
                () -> factIterative.apply(2), 2L)
            .addTest("Iterative: fact(5) = 120",
                () -> factIterative.apply(5), 120L)
            .addTest("Iterative: fact(10) = 3628800",
                () -> factIterative.apply(10), 3628800L)
            .addTest("Iterative: fact(15) = 1307674368000",
                () -> factIterative.apply(15), 1307674368000L)
            .addTest("Iterative: fact(20) = 2432902008176640000",
                () -> factIterative.apply(20), 2432902008176640000L)

            // -- Benchmark: all 4 at N=20 ---------------------
            .addBenchmark("Recursive N=20",
                () -> factRecursive.apply(20))
            .addBenchmark("Memoized N=20",
                () -> factMemoized.apply(20))
            .addBenchmark("Bottom-Up N=20",
                () -> factBottomUp.apply(20))
            .addBenchmark("Iterative N=20",
                () -> factIterative.apply(20))

            // -- Scaling: all 4 approaches (all O(N)) ---------
            .addScaling("N (recursive)",
                new int[]{100, 500, 1_000, 5_000, 10_000},
                n -> n,
                n -> factRecursive.apply(n))
            .addScaling("N (memoized)",
                new int[]{100, 500, 1_000, 5_000, 10_000},
                n -> n,
                n -> factMemoized.apply(n))
            .addScaling("N (bottom-up)",
                new int[]{100, 500, 1_000, 5_000, 10_000},
                n -> n,
                n -> factBottomUp.apply(n))
            .addScaling("N (iterative)",
                new int[]{100, 500, 1_000, 5_000, 10_000},
                n -> n,
                n -> factIterative.apply(n))

            // -- Random: Recursive vs Reference ---------------
            .addRandomTests("Recursive vs Reference (N in [0, 20])", 100, () -> {
                int n = rng.nextInt(21);
                long expected = referenceFact(n);
                return new TestHarness.Case<>(
                    "fact(" + n + ")",
                    () -> factRecursive.apply(n),
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

        // -- B1: Call counts for factRecursive(5) -------------
        total++;
        int[] counts = Question4_Factorial.callCountsFactorial5();
        int[] expectedCounts = {1, 1, 1, 1, 1, 1};
        if (counts != null && Arrays.equals(counts, expectedCounts)) {
            passed++;
            System.out.println("  \u2713 B1: Call counts for factRecursive(5) \u2014 PASS");
            System.out.println();
            System.out.println("    Here's the call tree for factorial(5):");
            System.out.println();
            System.out.println("      fact(5)");
            System.out.println("      \u2514\u2500\u2500 fact(4)");
            System.out.println("          \u2514\u2500\u2500 fact(3)");
            System.out.println("              \u2514\u2500\u2500 fact(2)");
            System.out.println("                  \u2514\u2500\u2500 fact(1)");
            System.out.println("                      \u2514\u2500\u2500 fact(0) = 1");
            System.out.println();
            System.out.println("    Each fact(k) is called exactly once \u2014 a straight line!");
            System.out.println("    Unlike Fibonacci's branching tree, factorial has NO overlapping");
            System.out.println("    subproblems. The call tree has N+1 nodes, not 2^N.");
        } else {
            System.out.println("  \u2717 B1: Call counts for factRecursive(5) \u2014 FAIL");
            System.out.println("    Expected: " + Arrays.toString(expectedCounts));
            System.out.println("    Got:      " + Arrays.toString(counts));
            System.out.println("    Hint: trace factorial(5). It calls fact(4), which calls fact(3),");
            System.out.println("    and so on. Each fact(k) is called how many times?");
        }
        System.out.println();

        // -- B2: Total calls for factRecursive(5) -------------
        total++;
        int totalCalls5 = Question4_Factorial.totalCallsRecursive5();
        if (totalCalls5 == 6) {
            passed++;
            System.out.println("  \u2713 B2: Total calls for factRecursive(5) = 6 \u2014 PASS");
            System.out.println("    6 total calls (N+1). Each call makes exactly one recursive call,");
            System.out.println("    forming a chain: fact(5)\u2192fact(4)\u2192fact(3)\u2192fact(2)\u2192fact(1)\u2192fact(0).");
        } else {
            System.out.println("  \u2717 B2: Total calls for factRecursive(5) \u2014 FAIL");
            System.out.println("    Expected: 6");
            System.out.println("    Got:      " + totalCalls5);
            System.out.println("    Hint: count every node in the call tree (including fact(5) itself).");
        }
        System.out.println();

        // -- B3: Total calls for factRecursive(10) ------------
        total++;
        int totalCalls10 = Question4_Factorial.totalCallsRecursive10();
        if (totalCalls10 == 11) {
            passed++;
            System.out.println("  \u2713 B3: Total calls for factRecursive(10) = 11 \u2014 PASS");
            System.out.println("    11 calls = N+1. Compare: Fibonacci had 177 calls for N=10!");
            System.out.println("    Factorial's recursion is linear, not exponential.");
        } else {
            System.out.println("  \u2717 B3: Total calls for factRecursive(10) \u2014 FAIL");
            System.out.println("    Expected: 11");
            System.out.println("    Got:      " + totalCalls10);
            System.out.println("    Hint: T(n) = 1 + T(n-1), with T(0) = 1. Each call spawns exactly one subcall.");
        }
        System.out.println();

        // -- B4: Total calls for factMemoized(5) --------------
        total++;
        int memoCalls5 = Question4_Factorial.totalCallsMemoized5();
        if (memoCalls5 == 6) {
            passed++;
            System.out.println("  \u2713 B4: Total calls for factMemoized(5) = 6 \u2014 PASS");
            System.out.println("    6 calls \u2014 exactly the same as without memoization!");
            System.out.println("    Since each fact(k) is already called only once, there's nothing");
            System.out.println("    to cache. Memoization adds overhead with no benefit.");
            System.out.println("    This is the key contrast with Fibonacci: overlapping subproblems");
            System.out.println("    are what make memoization worthwhile.");
        } else {
            System.out.println("  \u2717 B4: Total calls for factMemoized(5) \u2014 FAIL");
            System.out.println("    Expected: 6");
            System.out.println("    Got:      " + memoCalls5);
            System.out.println("    Hint: since each fact(k) is called exactly once even without");
            System.out.println("    memoization, does caching help?");
        }
        System.out.println();

        // -- B5-B12: Complexity Questions ---------------------

        // B5: Time complexity of recursive
        total++;
        String tcRecursive = normalize(Question4_Factorial.timeComplexityRecursive());
        if (tcRecursive.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B5: Time complexity of factRecursive = O(N) \u2014 PASS");
            System.out.println("    Only N+1 calls, each doing O(1) work. NOT exponential like Fibonacci!");
            System.out.println("    The call tree is a straight line, not a binary tree.");
        } else {
            System.out.println("  \u2717 B5: Time complexity of factRecursive \u2014 FAIL");
            System.out.println("    Got: " + Question4_Factorial.timeComplexityRecursive());
            System.out.println("    Hint: how many calls does factRecursive(n) make total?");
        }
        System.out.println();

        // B6: Space complexity of recursive
        total++;
        String scRecursive = normalize(Question4_Factorial.spaceComplexityRecursive());
        if (scRecursive.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B6: Space complexity of factRecursive = O(N) \u2014 PASS");
            System.out.println("    The call stack goes N levels deep:");
            System.out.println("    fact(5)\u2192fact(4)\u2192...\u2192fact(0).");
        } else {
            System.out.println("  \u2717 B6: Space complexity of factRecursive \u2014 FAIL");
            System.out.println("    Got: " + Question4_Factorial.spaceComplexityRecursive());
            System.out.println("    Hint: how deep does the call stack get?");
        }
        System.out.println();

        // B7: Time complexity of memoized
        total++;
        String tcMemoized = normalize(Question4_Factorial.timeComplexityMemoized());
        if (tcMemoized.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B7: Time complexity of factMemoized = O(N) \u2014 PASS");
            System.out.println("    Same as recursive \u2014 memoization doesn't change the work here.");
        } else {
            System.out.println("  \u2717 B7: Time complexity of factMemoized \u2014 FAIL");
            System.out.println("    Got: " + Question4_Factorial.timeComplexityMemoized());
            System.out.println("    Hint: does memoization reduce the number of calls for factorial?");
        }
        System.out.println();

        // B8: Space complexity of memoized
        total++;
        String scMemoized = normalize(Question4_Factorial.spaceComplexityMemoized());
        if (scMemoized.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B8: Space complexity of factMemoized = O(N) \u2014 PASS");
            System.out.println("    The memo array has N+1 entries plus the call stack is N deep.");
            System.out.println("    Both O(N).");
        } else {
            System.out.println("  \u2717 B8: Space complexity of factMemoized \u2014 FAIL");
            System.out.println("    Got: " + Question4_Factorial.spaceComplexityMemoized());
            System.out.println("    Hint: consider the memo array size AND the call stack depth.");
        }
        System.out.println();

        // B9: Time complexity of bottom-up
        total++;
        String tcBottomUp = normalize(Question4_Factorial.timeComplexityBottomUp());
        if (tcBottomUp.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B9: Time complexity of factBottomUp = O(N) \u2014 PASS");
            System.out.println("    A single loop from 1 to N, each iteration doing O(1) work.");
        } else {
            System.out.println("  \u2717 B9: Time complexity of factBottomUp \u2014 FAIL");
            System.out.println("    Got: " + Question4_Factorial.timeComplexityBottomUp());
            System.out.println("    Hint: how many iterations does the loop do?");
        }
        System.out.println();

        // B10: Space complexity of bottom-up
        total++;
        String scBottomUp = normalize(Question4_Factorial.spaceComplexityBottomUp());
        if (scBottomUp.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B10: Space complexity of factBottomUp = O(N) \u2014 PASS");
            System.out.println("    The dp[] array has N+1 entries = O(N) space.");
        } else {
            System.out.println("  \u2717 B10: Space complexity of factBottomUp \u2014 FAIL");
            System.out.println("    Got: " + Question4_Factorial.spaceComplexityBottomUp());
            System.out.println("    Hint: how big is the dp[] array?");
        }
        System.out.println();

        // B11: Time complexity of iterative
        total++;
        String tcIterative = normalize(Question4_Factorial.timeComplexityIterative());
        if (tcIterative.equals("O(N)")) {
            passed++;
            System.out.println("  \u2713 B11: Time complexity of factIterative = O(N) \u2014 PASS");
            System.out.println("    Same as bottom-up: one loop from 1 to N.");
        } else {
            System.out.println("  \u2717 B11: Time complexity of factIterative \u2014 FAIL");
            System.out.println("    Got: " + Question4_Factorial.timeComplexityIterative());
        }
        System.out.println();

        // B12: Space complexity of iterative
        total++;
        String scIterative = normalize(Question4_Factorial.spaceComplexityIterative());
        if (scIterative.equals("O(1)")) {
            passed++;
            System.out.println("  \u2713 B12: Space complexity of factIterative = O(1) \u2014 PASS");
            System.out.println("    Only one accumulator variable regardless of N.");
            System.out.println("    This is the most space-efficient approach.");
        } else {
            System.out.println("  \u2717 B12: Space complexity of factIterative \u2014 FAIL");
            System.out.println("    Got: " + Question4_Factorial.spaceComplexityIterative());
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

    private static long referenceFact(int n) {
        long result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }

    /** Normalize complexity strings: trim, uppercase, remove spaces. */
    private static String normalize(String s) {
        if (s == null) {
            return "";
        }
        return s.trim().toUpperCase().replaceAll("\\s+", "");
    }
}
