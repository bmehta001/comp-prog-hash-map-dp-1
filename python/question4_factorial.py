"""
===============================================================
 PROBLEM 4 -- Factorial: Four Implementations + Analysis
===============================================================

 The factorial function is defined as:
   n! = n × (n-1) × ... × 1
   0! = 1

 First few values: 1, 1, 2, 6, 24, 120, 720, 5040, ...

 ===============================================================
  PART A -- Code Implementations
 ===============================================================

 Implement FOUR different approaches to compute n!:

 --- Approach 1: Naive Recursive ----------------------------------
 Base case: 0! = 1
 Recursive case: n! = n * (n-1)!

 --- Approach 2: Memoized (Top-Down DP) ---------------------------
 Same recursive structure, but cache results in a dict.
 Before computing n!, check if it's already been computed.

 --- Approach 3: Bottom-Up DP (Array) -----------------------------
 Build the answer from 0! up to n! using a dp list.
 Fill dp[0] = 1, then dp[i] = i * dp[i-1] for i >= 1.

 --- Approach 4: Iterative (Accumulator) --------------------------
 Use a single accumulator variable, multiply from 1 to n.
 No list needed -- just one running product.

 ===============================================================
  PART B -- Analysis Questions
 ===============================================================

 The main goal of this problem is for you to TRACE through the
 recursive calls and DISCOVER the time/space complexity yourself.

 Below are functions that return YOUR answers. Fill them in by
 hand (not by running code). The test harness will check them.

 When you get an answer correct, you'll see detailed feedback
 explaining WHY that answer is correct.

 KEY INSIGHT: Unlike Fibonacci, factorial has NO overlapping
 subproblems. The call tree is a straight line, not a branching
 tree. This means memoization provides no benefit!

 Note: for large N with memoized recursion, you may need to call
 sys.setrecursionlimit() to avoid hitting Python's default limit
 of 1000.

 Run:
   python question4_factorial.py
===============================================================
"""

import sys
from question4_tests import build_code_harness, run_analysis


# ===============================================================
#  PART A -- Code Implementations
# ===============================================================

def fact_recursive(n: int) -> int:
    """
    Naive recursive factorial.

    Base case: fact(0) = 1
    Recursive case: fact(n) = n * fact(n-1)
    """
    # TODO: Implement naive recursive factorial
    return -1


def fact_memoized(n: int) -> int:
    """
    Memoized (top-down DP) factorial.

    Create a memo dict. If memo[n] is set, return it.
    Otherwise compute, store in memo, and return.
    """
    # TODO: Implement memoized (top-down DP) factorial
    return -1


def fact_bottom_up(n: int) -> int:
    """
    Bottom-up DP factorial with an array.

    Create a list dp of size n+1.
    Set dp[0] = 1.
    Fill dp[i] = i * dp[i-1] for i from 1 to n.
    Return dp[n].
    """
    # TODO: Implement bottom-up DP factorial
    return -1


def fact_iterative(n: int) -> int:
    """
    Iterative factorial with an accumulator.

    Use one variable: result = 1
    Loop from 1 to n, multiplying: result *= i
    No list needed -- just one running product.
    """
    # TODO: Implement iterative factorial
    return -1


# ===============================================================
#  PART B -- Analysis Questions
#
#  Answer these by tracing through the code BY HAND.
#  You'll learn the most by working through these on paper
#  rather than just running the code.
# ===============================================================

def call_counts_factorial_5() -> list:
    """
    B1: When fact_recursive(5) runs, how many times is each fact(k) called?

    Return a list of length 6 where index k = number of times fact(k)
    is called. For example, if fact(3) is called 2 times, arr[3] = 2.

    Hint: draw the call tree on paper starting from fact(5).
    fact(5) calls fact(4). fact(4) calls fact(3). And so on...
    Unlike Fibonacci, there's only ONE recursive call per level.
    """
    return [0, 0, 0, 0, 0, 0]


def total_calls_recursive_5() -> int:
    """
    B2: What is the TOTAL number of function calls made by fact_recursive(5)?
    Count every call, including the initial call to fact(5) itself.
    """
    return 0


def total_calls_recursive_10() -> int:
    """
    B3: What is the TOTAL number of function calls made by fact_recursive(10)?
    You don't need to draw the full tree -- find the pattern from smaller examples.

    Hint: Let T(n) = total calls for fact_recursive(n).
    T(0) = 1. What is T(n) in terms of T(n-1)?
    """
    return 0


def total_calls_memoized_5() -> int:
    """
    B4: What is the TOTAL number of function calls made by fact_memoized(5)?
    With memoization, each fact(k) is computed at most once.
    But since each fact(k) is already called only once in the
    recursive version, does memoization help here?

    Hint: trace through the memoized version. Compare to B2.
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
    """B5: Time complexity of fact_recursive(n)"""
    return ""


def space_complexity_recursive() -> str:
    """B6: Space complexity of fact_recursive(n) -- think about call stack depth"""
    return ""


def time_complexity_memoized() -> str:
    """B7: Time complexity of fact_memoized(n)"""
    return ""


def space_complexity_memoized() -> str:
    """B8: Space complexity of fact_memoized(n) -- memo dict + call stack"""
    return ""


def time_complexity_bottom_up() -> str:
    """B9: Time complexity of fact_bottom_up(n)"""
    return ""


def space_complexity_bottom_up() -> str:
    """B10: Space complexity of fact_bottom_up(n) -- the dp list"""
    return ""


def time_complexity_iterative() -> str:
    """B11: Time complexity of fact_iterative(n)"""
    return ""


def space_complexity_iterative() -> str:
    """B12: Space complexity of fact_iterative(n) -- how many variables?"""
    return ""


# ===============================================================

if __name__ == "__main__":
    # Part A: Code implementations
    code_passed = build_code_harness(
        fact_recursive, fact_memoized, fact_bottom_up, fact_iterative
    ).run()  # Tip: change to .run_quick() for faster feedback

    # Part B: Analysis questions
    analysis_passed = run_analysis()

    if not code_passed or not analysis_passed:
        sys.exit(1)
