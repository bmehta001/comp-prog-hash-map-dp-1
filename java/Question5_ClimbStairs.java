/**
 * ===========================================================
 *  PROBLEM 5 -- Climbing Stairs: Three Implementations
 * ===========================================================
 *
 *  You are climbing a staircase with N steps. Each time you can climb
 *  either 1 step or 2 steps. In how many distinct ways can you reach
 *  the top?
 *
 *  Examples:
 *    climb(1) = 1     (1 way: [1])
 *    climb(2) = 2     (2 ways: [1+1], [2])
 *    climb(3) = 3     (3 ways: [1+1+1], [1+2], [2+1])
 *
 *  Your task: implement three different approaches to compute ways(n).
 *  (See HINTS.md if you want to discover a helpful pattern.)
 *
 *  --- Approach 1: Naive Recursive ---------------------------
 *
 *  Direct translation of the recurrence relation.
 *  Simple but EXPONENTIAL -- O(2^N) time!
 *
 *  Why so slow? The same subproblems are recomputed many times.
 *  For example, climb(5) calls climb(4) + climb(3). Then climb(4)
 *  calls climb(3) + climb(2). So climb(3) is computed TWICE.
 *  The redundancy grows exponentially.
 *
 *  Call tree for climb(5) -- 15 total calls:
 *
 *    climb(5)
 *    |-- climb(4)
 *    |   |-- climb(3)
 *    |   |   |-- climb(2) = 2
 *    |   |   \-- climb(1) = 1
 *    |   \-- climb(2) = 2
 *    \-- climb(3)
 *        |-- climb(2) = 2
 *        \-- climb(1) = 1
 *
 *  Note: 15 calls for climb(5). With memoization, only 9 calls.
 *  Iterative: just N-2 iterations (3 for climb(5)).
 *
 *  --- Approach 2: Memoized (Top-Down DP) --------------------
 *
 *  Same recursive structure, but cache results in an array.
 *  Before computing ways(k), check if it's already been computed.
 *  Each ways(k) is computed only once -> O(N) time, O(N) space.
 *
 *  --- Approach 3: Iterative (Bottom-Up DP) ------------------
 *
 *  Build the answer from ways(1) up to ways(n) using only two
 *  variables. No recursion, no extra array -- just a simple loop.
 *  O(N) time, O(1) space. This is the most efficient approach.
 *
 *  Constraints:
 *    1 <= N <= 60
 *
 *  Compile & run:
 *    javac *.java
 *    java Question5_ClimbStairs
 * ===========================================================
 */
public class Question5_ClimbStairs {

    public static long solveRecursive(int n) {
        // TODO: Implement naive recursive solution
        // Base cases: ways(1) = 1, ways(2) = 2
        // Recursive case: ways(n) = ways(n-1) + ways(n-2)
        return -1;
    }

    public static long solveMemoized(int n) {
        // TODO: Implement top-down DP with memoization
        // Create a long[] memo of size n+1, initialized to -1
        // Before computing ways(k), check if memo[k] != -1
        return -1;
    }

    public static long solveIterative(int n) {
        // TODO: Implement bottom-up DP (iterative)
        // Use two variables: prev and curr
        // Loop from 3 to n, building up the answer
        return -1;
    }

    public static void main(String[] args) {
        boolean passed = Question5_Tests.buildHarness(
                Question5_ClimbStairs::solveRecursive,
                Question5_ClimbStairs::solveMemoized,
                Question5_ClimbStairs::solveIterative)
            .run();   // Tip: change to .runQuick() for faster feedback
        if (!passed) {
            System.exit(1);
        }
    }
}
