"""
===============================================================
 PROBLEM 5 -- Climbing Stairs: Three Implementations
===============================================================

 You are climbing a staircase with N steps. Each time you can climb
 either 1 step or 2 steps. In how many distinct ways can you reach
 the top?

 Examples:
   climb(1) = 1     (1 way: [1])
   climb(2) = 2     (2 ways: [1+1], [2])
   climb(3) = 3     (3 ways: [1+1+1], [1+2], [2+1])

 Your task: implement three different approaches to compute ways(n).
 (See HINTS.md if you want to discover a helpful pattern.)

 --- Approach 1: Naive Recursive ---------------------------------

 Direct translation of the recurrence relation.
 Simple but EXPONENTIAL -- O(2^N) time!

 Why so slow? The same subproblems are recomputed many times.
 For example, climb(5) calls climb(4) + climb(3). Then climb(4)
 calls climb(3) + climb(2). So climb(3) is computed TWICE.
 The redundancy grows exponentially.

 Call tree for climb(5) -- 15 total calls:

   climb(5)
   |-- climb(4)
   |   |-- climb(3)
   |   |   |-- climb(2) = 2
   |   |   +-- climb(1) = 1
   |   +-- climb(2) = 2
   +-- climb(3)
       |-- climb(2) = 2
       +-- climb(1) = 1

 Note: 15 calls for climb(5). With memoization, only 9 calls.
 Iterative: just N-2 iterations (3 for climb(5)).

 --- Approach 2: Memoized (Top-Down DP) --------------------------

 Same recursive structure, but cache results in a dict or list.
 Before computing ways(k), check if it's already been computed.
 Each ways(k) is computed only once -> O(N) time, O(N) space.

 --- Approach 3: Iterative (Bottom-Up DP) ------------------------

 Build the answer from ways(1) up to ways(n) using only two
 variables. No recursion, no extra data structure -- just a simple
 loop. O(N) time, O(1) space. This is the most efficient approach.

 Constraints:
   1 <= N <= 60

 Run:
   python question5_climb_stairs.py
===============================================================
"""

import sys
from question5_tests import build_harness


def solve_recursive(n: int) -> int:
    """
    Naive recursive climbing stairs.

    Base cases: ways(1) = 1, ways(2) = 2
    Recursive case: ways(n) = ways(n-1) + ways(n-2)
    """
    # TODO: Implement naive recursive solution
    return -1


def solve_memoized(n: int) -> int:
    """
    Memoized (top-down DP) climbing stairs.

    Create a memo dict or list. If memo[n] is set, return it.
    Otherwise compute, store in memo, and return.
    """
    # TODO: Implement top-down DP with memoization
    return -1


def solve_iterative(n: int) -> int:
    """
    Iterative (bottom-up DP) climbing stairs.

    Use two variables: prev = 1, curr = 2
    Loop from 3 to n, updating: next_val = prev + curr
    """
    # TODO: Implement bottom-up DP (iterative)
    return -1


if __name__ == "__main__":
    passed = build_harness(solve_recursive, solve_memoized, solve_iterative) \
        .run()   # Tip: change to .run_quick() for faster feedback
    if not passed:
        sys.exit(1)
