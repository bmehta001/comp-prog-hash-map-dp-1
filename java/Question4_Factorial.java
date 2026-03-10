/**
 * ═══════════════════════════════════════════════════════════
 *  PROBLEM 4 — Factorial: Four Implementations + Analysis
 * ═══════════════════════════════════════════════════════════
 *
 *  The factorial function is defined as:
 *    n! = n × (n-1) × ... × 1, with 0! = 1
 *
 *  First few values: 1, 1, 2, 6, 24, 120, 720, 5040, ...
 *
 *  ═══════════════════════════════════════════════════════════
 *   PART A — Code Implementations
 *  ═══════════════════════════════════════════════════════════
 *
 *  Implement FOUR different approaches to compute n!:
 *
 *  ─── Approach 1: Naive Recursive ───────────────────────────
 *  Direct translation of the recurrence relation.
 *  Base case: 0! = 1. Recursive case: n! = n * (n-1)!
 *
 *  ─── Approach 2: Memoized (Top-Down DP) ────────────────────
 *  Same recursive structure, but cache results in a memo array.
 *  Before computing fact(k), check if it's already been computed.
 *
 *  ─── Approach 3: Bottom-Up DP (Array) ──────────────────────
 *  Build the answer from fact(0) up to fact(n) using a dp[] array.
 *  Fill dp[0] = 1, then dp[i] = i * dp[i-1] for i from 1 to n.
 *
 *  ─── Approach 4: Iterative (Accumulator) ───────────────────
 *  Same bottom-up idea, but instead of storing the whole array,
 *  keep only one accumulator variable.
 *
 *  ═══════════════════════════════════════════════════════════
 *   PART B — Analysis Questions
 *  ═══════════════════════════════════════════════════════════
 *
 *  The main goal of this problem is for you to TRACE through the
 *  recursive calls and DISCOVER the time/space complexity yourself.
 *
 *  KEY INSIGHT: Unlike Fibonacci, factorial has NO overlapping
 *  subproblems. The call tree is a straight line, not a branching
 *  tree. This means memoization provides no benefit!
 *
 *  Below are functions that return YOUR answers. Fill them in by
 *  hand (not by running code). The test harness will check them.
 *
 *  When you get an answer correct, you'll see detailed feedback
 *  explaining WHY that answer is correct.
 *
 *  Compile & run:
 *    javac *.java
 *    java Question4_Factorial
 * ═══════════════════════════════════════════════════════════
 */
import java.util.Arrays;

public class Question4_Factorial {

    // ═══════════════════════════════════════════════════════
    //  PART A — Code Implementations
    // ═══════════════════════════════════════════════════════

    public static long factRecursive(int n) {
        // TODO: Implement naive recursive factorial
        // Base case: 0! = 1 (also 1! = 1)
        // Recursive case: n! = n * (n-1)!
        return -1;
    }

    public static long factMemoized(int n) {
        // TODO: Implement memoized (top-down DP) factorial
        // Create a long[] memo of size n+1, initialized to -1
        // Use a helper that checks memo[k] before computing
        // If memo[k] != -1, return it; otherwise compute, store, return
        return -1;
    }

    public static long factBottomUp(int n) {
        // TODO: Implement bottom-up DP factorial with an array
        // Create a long[] dp of size n+1
        // Set dp[0] = 1
        // Fill dp[i] = i * dp[i-1] for i from 1 to n
        // Return dp[n]
        return -1;
    }

    public static long factIterative(int n) {
        // TODO: Implement iterative factorial with an accumulator
        // Use one variable: result = 1
        // Loop from 2 to n, multiplying: result *= i
        // No array needed — just one running product
        return -1;
    }

    // ═══════════════════════════════════════════════════════
    //  PART B — Analysis Questions
    //
    //  Answer these by tracing through the code BY HAND.
    //  You'll learn the most by working through these on paper
    //  rather than just running the code.
    // ═══════════════════════════════════════════════════════

    /**
     * B1: When factRecursive(5) runs, how many times is each fact(k) called?
     *
     * Return an array of length 6 where index k = number of times fact(k)
     * is called. For example, if fact(3) is called 2 times, arr[3] = 2.
     *
     * Hint: trace fact(5). It calls fact(4), which calls fact(3), etc.
     * How many times is each fact(k) called?
     */
    public static int[] callCountsFactorial5() {
        // TODO: Fill in the call counts for fact(0) through fact(5)
        //       arr[0] = times fact(0) is called
        //       arr[1] = times fact(1) is called
        //       ...
        //       arr[5] = times fact(5) is called
        return new int[]{0, 0, 0, 0, 0, 0};
    }

    /**
     * B2: What is the TOTAL number of function calls made by factRecursive(5)?
     * Count every call, including the initial call to fact(5) itself.
     */
    public static int totalCallsRecursive5() {
        return 0;
    }

    /**
     * B3: What is the TOTAL number of function calls made by factRecursive(10)?
     * You don't need to draw the full tree — find the pattern from smaller examples.
     *
     * Hint: Let T(n) = total calls. Each call makes exactly ONE recursive call
     * (not two). So T(n) = 1 + T(n-1), with T(0) = 1.
     */
    public static int totalCallsRecursive10() {
        return 0;
    }

    /**
     * B4: What is the TOTAL number of function calls made by factMemoized(5)?
     * With memoization, each fact(k) is computed at most once.
     *
     * Hint: since factorial has no overlapping subproblems, think about
     * whether memoization changes the count.
     */
    public static int totalCallsMemoized5() {
        return 0;
    }

    // ─── Complexity Questions ────────────────────────────────
    //
    // For each approach, state the time and space complexity.
    // Return EXACTLY one of these strings:
    //   "O(1)", "O(N)", "O(N^2)", "O(2^N)"
    //
    // Think about:
    //   Time  = how many operations as N grows?
    //   Space = how much extra memory (beyond the input)?
    //          For recursive approaches, consider the call stack.

    /** B5: Time complexity of factRecursive(n) */
    public static String timeComplexityRecursive() {
        return "";
    }

    /** B6: Space complexity of factRecursive(n) — think about call stack depth */
    public static String spaceComplexityRecursive() {
        return "";
    }

    /** B7: Time complexity of factMemoized(n) */
    public static String timeComplexityMemoized() {
        return "";
    }

    /** B8: Space complexity of factMemoized(n) — memo array + call stack */
    public static String spaceComplexityMemoized() {
        return "";
    }

    /** B9: Time complexity of factBottomUp(n) */
    public static String timeComplexityBottomUp() {
        return "";
    }

    /** B10: Space complexity of factBottomUp(n) — the dp[] array */
    public static String spaceComplexityBottomUp() {
        return "";
    }

    /** B11: Time complexity of factIterative(n) */
    public static String timeComplexityIterative() {
        return "";
    }

    /** B12: Space complexity of factIterative(n) — how many variables? */
    public static String spaceComplexityIterative() {
        return "";
    }

    // ═══════════════════════════════════════════════════════

    public static void main(String[] args) {
        // Part A: Code implementations
        boolean codePassed = Question4_Tests.buildCodeHarness(
                Question4_Factorial::factRecursive,
                Question4_Factorial::factMemoized,
                Question4_Factorial::factBottomUp,
                Question4_Factorial::factIterative)
            .run();

        // Part B: Analysis questions
        boolean analysisPassed = Question4_Tests.runAnalysis();

        if (!codePassed || !analysisPassed) {
            System.exit(1);
        }
    }
}
