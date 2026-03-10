"""
===============================================================
 PROBLEM 3 -- Fibonacci: Four Implementations + Analysis
===============================================================

 The Fibonacci sequence is defined as:
   F(0) = 0
   F(1) = 1
   F(n) = F(n-1) + F(n-2)   for n >= 2

 First few values: 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...

 ===============================================================
  PART A -- Code Implementations
 ===============================================================

 Implement FOUR different approaches to compute F(n):

 --- Approach 1: Naive Recursive ----------------------------------
 Direct translation of the recurrence relation.
 Think about: why is this so slow?

 --- Approach 2: Memoized (Top-Down DP) ---------------------------
 Same recursive structure, but cache results in a dict or list.
 Before computing F(k), check if it's already been computed.

 Tip: you can also use Python's @functools.lru_cache decorator,
 but implementing your own memo dict teaches the concept better.

 --- Approach 3: Bottom-Up DP (Array) -----------------------------
 Build the answer from F(0) up to F(n) using a dp list.
 Fill dp[0], dp[1], then dp[i] = dp[i-1] + dp[i-2] for i >= 2.

 --- Approach 4: Iterative (Two Variables) ------------------------
 Same bottom-up idea, but instead of storing the whole list,
 keep only the two most recent values.

 ===============================================================
  PART B -- Analysis Questions
 ===============================================================

 The main goal of this problem is for you to TRACE through the
 recursive calls and DISCOVER the time/space complexity yourself.

 Below are functions that return YOUR answers. Fill them in by
 hand (not by running code). The test harness will check them.

 When you get an answer correct, you'll see detailed feedback
 explaining WHY that answer is correct.

 Note: for large N with memoized recursion, you may need to call
 sys.setrecursionlimit() to avoid hitting Python's default limit
 of 1000.

 Run:
   python question3_fibonacci.py
===============================================================
"""

import sys
from question3_tests import build_code_harness, run_analysis


# ===============================================================
#  PART A -- Code Implementations
# ===============================================================

def fib_recursive(n: int) -> int:
    """
    Naive recursive fibonacci.

    Base cases: fib(0) = 0, fib(1) = 1
    Recursive case: fib(n) = fib(n-1) + fib(n-2)
    """
    # TODO: Implement naive recursive fibonacci
    return -1


def fib_memoized(n: int) -> int:
    """
    Memoized (top-down DP) fibonacci.

    Create a memo dict or list. If memo[n] is set, return it.
    Otherwise compute, store in memo, and return.
    """
    # TODO: Implement memoized (top-down DP) fibonacci
    return -1


def fib_bottom_up(n: int) -> int:
    """
    Bottom-up DP fibonacci with an array.

    Create a list dp of size n+1.
    Set dp[0] = 0, dp[1] = 1.
    Fill dp[i] = dp[i-1] + dp[i-2] for i from 2 to n.
    Return dp[n].
    """
    # TODO: Implement bottom-up DP fibonacci
    return -1


def fib_iterative(n: int) -> int:
    """
    Iterative fibonacci with two variables.

    Use two variables: prev = 0, curr = 1
    Loop from 2 to n, updating: next_val = prev + curr
    No list needed -- just shift the two variables each iteration.
    """
    # TODO: Implement iterative fibonacci
    return -1


# ===============================================================
#  PART B -- Analysis Questions
#
#  Answer these by tracing through the code BY HAND.
#  You'll learn the most by working through these on paper
#  rather than just running the code.
# ===============================================================

def call_counts_fib5() -> list:
    """
    B1: When fib_recursive(5) runs, how many times is each fib(k) called?

    Return a list of length 6 where index k = number of times fib(k)
    is called. For example, if fib(3) is called 2 times, arr[3] = 2.

    Hint: draw the full call tree on paper starting from fib(5).
    fib(5) calls fib(4) and fib(3). Then fib(4) calls fib(3) and fib(2).
    Keep going until you reach base cases fib(1) and fib(0).
    Count how many times each fib(k) appears in your tree.
    """
    return [0, 0, 0, 0, 0, 0]


def total_calls_recursive_5() -> int:
    """
    B2: What is the TOTAL number of function calls made by fib_recursive(5)?
    Count every call, including the initial call to fib(5) itself.
    """
    return 0


def total_calls_recursive_10() -> int:
    """
    B3: What is the TOTAL number of function calls made by fib_recursive(10)?
    You don't need to draw the full tree -- find the pattern from smaller examples.

    Hint: Let T(n) = total calls for fib_recursive(n).
    T(0) = 1, T(1) = 1. What is T(n) in terms of T(n-1) and T(n-2)?
    """
    return 0


def total_calls_memoized_5() -> int:
    """
    B4: What is the TOTAL number of function calls made by fib_memoized(5)?
    With memoization, each fib(k) is computed at most once.
    But there are still calls that hit the cache and return immediately.

    Hint: trace through the memoized version. The first time fib(k) is
    called, it recurses. The second time, it returns from the cache
    immediately (still counts as a call, but no further recursion).
    """
    return 0


# --- Complexity Questions-----------------------------------------
#
# For each approach, state the time and space complexity.
# Return EXACTLY one of these strings:
#   "O(1)", "O(N)", "O(N^2)", "O(2^N)"
#
# Think about:
#   Time  = how many operations as N grows?
#   Space = how much extra memory (beyond the input)?
#           For recursive approaches, consider the call stack.

def time_complexity_recursive() -> str:
    """B5: Time complexity of fib_recursive(n)"""
    return ""


def space_complexity_recursive() -> str:
    """B6: Space complexity of fib_recursive(n) -- think about call stack depth"""
    return ""


def time_complexity_memoized() -> str:
    """B7: Time complexity of fib_memoized(n)"""
    return ""


def space_complexity_memoized() -> str:
    """B8: Space complexity of fib_memoized(n) -- memo dict + call stack"""
    return ""


def time_complexity_bottom_up() -> str:
    """B9: Time complexity of fib_bottom_up(n)"""
    return ""


def space_complexity_bottom_up() -> str:
    """B10: Space complexity of fib_bottom_up(n) -- the dp list"""
    return ""


def time_complexity_iterative() -> str:
    """B11: Time complexity of fib_iterative(n)"""
    return ""


def space_complexity_iterative() -> str:
    """B12: Space complexity of fib_iterative(n) -- how many variables?"""
    return ""


# ===============================================================

if __name__ == "__main__":
    # Part A: Code implementations
    code_passed = build_code_harness(
        fib_recursive, fib_memoized, fib_bottom_up, fib_iterative
    ).run()  # Tip: change to .run_quick() for faster feedback

    # Part B: Analysis questions
    analysis_passed = run_analysis()

    if not code_passed or not analysis_passed:
        sys.exit(1)
