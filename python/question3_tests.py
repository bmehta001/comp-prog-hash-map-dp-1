"""
Test infrastructure for Problem 2 -- Fibonacci: Four Implementations + Analysis.
Contains reference solution, benchmarks, scaling analysis, correctness tests,
and analysis question checking with feedback.
"""

import random
import sys
from test_harness import TestHarness, Case

# Allow deep recursion for memoized fibonacci at large N
sys.setrecursionlimit(20_000)


# ===============================================================
#  PART A -- Code Implementation Tests
# ===============================================================

def build_code_harness(fib_recursive, fib_memoized, fib_bottom_up, fib_iterative):
    """Build a fully configured test harness for Problem 2 code implementations."""
    rng = random.Random(42)

    return TestHarness("Fibonacci \u2014 Four Implementations + Analysis") \
        \
        .add_test("Recursive: fib(0) = 0",
            lambda: fib_recursive(0), 0) \
        .add_test("Recursive: fib(1) = 1",
            lambda: fib_recursive(1), 1) \
        .add_test("Recursive: fib(2) = 1",
            lambda: fib_recursive(2), 1) \
        .add_test("Recursive: fib(5) = 5",
            lambda: fib_recursive(5), 5) \
        .add_test("Recursive: fib(10) = 55",
            lambda: fib_recursive(10), 55) \
        .add_test("Recursive: fib(20) = 6765",
            lambda: fib_recursive(20), 6765) \
        \
        .add_test("Memoized: fib(0) = 0",
            lambda: fib_memoized(0), 0) \
        .add_test("Memoized: fib(1) = 1",
            lambda: fib_memoized(1), 1) \
        .add_test("Memoized: fib(2) = 1",
            lambda: fib_memoized(2), 1) \
        .add_test("Memoized: fib(5) = 5",
            lambda: fib_memoized(5), 5) \
        .add_test("Memoized: fib(10) = 55",
            lambda: fib_memoized(10), 55) \
        .add_test("Memoized: fib(20) = 6765",
            lambda: fib_memoized(20), 6765) \
        .add_test("Memoized: fib(50) = 12586269025",
            lambda: fib_memoized(50), 12586269025) \
        \
        .add_test("Bottom-Up: fib(0) = 0",
            lambda: fib_bottom_up(0), 0) \
        .add_test("Bottom-Up: fib(1) = 1",
            lambda: fib_bottom_up(1), 1) \
        .add_test("Bottom-Up: fib(2) = 1",
            lambda: fib_bottom_up(2), 1) \
        .add_test("Bottom-Up: fib(5) = 5",
            lambda: fib_bottom_up(5), 5) \
        .add_test("Bottom-Up: fib(10) = 55",
            lambda: fib_bottom_up(10), 55) \
        .add_test("Bottom-Up: fib(20) = 6765",
            lambda: fib_bottom_up(20), 6765) \
        .add_test("Bottom-Up: fib(50) = 12586269025",
            lambda: fib_bottom_up(50), 12586269025) \
        \
        .add_test("Iterative: fib(0) = 0",
            lambda: fib_iterative(0), 0) \
        .add_test("Iterative: fib(1) = 1",
            lambda: fib_iterative(1), 1) \
        .add_test("Iterative: fib(2) = 1",
            lambda: fib_iterative(2), 1) \
        .add_test("Iterative: fib(5) = 5",
            lambda: fib_iterative(5), 5) \
        .add_test("Iterative: fib(10) = 55",
            lambda: fib_iterative(10), 55) \
        .add_test("Iterative: fib(20) = 6765",
            lambda: fib_iterative(20), 6765) \
        .add_test("Iterative: fib(50) = 12586269025",
            lambda: fib_iterative(50), 12586269025) \
        \
        .add_benchmark("Recursive N=30",
            lambda: fib_recursive(30)) \
        .add_benchmark("Memoized N=30",
            lambda: fib_memoized(30)) \
        .add_benchmark("Bottom-Up N=30",
            lambda: fib_bottom_up(30)) \
        .add_benchmark("Iterative N=30",
            lambda: fib_iterative(30)) \
        \
        .add_scaling("N (memoized)",
            [100, 500, 1_000, 5_000, 10_000],
            lambda n: n,
            lambda n: fib_memoized(n)) \
        .add_scaling("N (bottom-up)",
            [100, 500, 1_000, 5_000, 10_000],
            lambda n: n,
            lambda n: fib_bottom_up(n)) \
        .add_scaling("N (iterative)",
            [100, 500, 1_000, 5_000, 10_000],
            lambda n: n,
            lambda n: fib_iterative(n)) \
        \
        .add_random_tests("Recursive vs Reference (N in [0, 40])", 100,
            lambda: _make_random_case(rng, fib_recursive))


# ===============================================================
#  PART B -- Analysis Question Checking
# ===============================================================

def run_analysis():
    """Check all 12 analysis questions and provide feedback."""
    # Import analysis functions from the student file
    from question3_fibonacci import (
        call_counts_fib5, total_calls_recursive_5, total_calls_recursive_10,
        total_calls_memoized_5, time_complexity_recursive, space_complexity_recursive,
        time_complexity_memoized, space_complexity_memoized, time_complexity_bottom_up,
        space_complexity_bottom_up, time_complexity_iterative, space_complexity_iterative
    )

    border = "======================================================="
    print()
    print(border)
    print("  Part B: Analysis Questions")
    print(border)
    print()

    total = 0
    passed = 0

    # -- B1: Call counts for fib_recursive(5) --
    total += 1
    counts = call_counts_fib5()
    expected_counts = [3, 5, 3, 2, 1, 1]
    if counts is not None and list(counts) == expected_counts:
        passed += 1
        print("  \u2713 B1: Call counts for fib_recursive(5) \u2014 PASS")
        print()
        print("    Here's the full call tree you should have drawn:")
        print()
        print("      fib(5)")
        print("      \u251c\u2500\u2500 fib(4)")
        print("      \u2502   \u251c\u2500\u2500 fib(3)")
        print("      \u2502   \u2502   \u251c\u2500\u2500 fib(2)")
        print("      \u2502   \u2502   \u2502   \u251c\u2500\u2500 fib(1) = 1")
        print("      \u2502   \u2502   \u2502   \u2514\u2500\u2500 fib(0) = 0")
        print("      \u2502   \u2502   \u2514\u2500\u2500 fib(1) = 1")
        print("      \u2502   \u2514\u2500\u2500 fib(2)")
        print("      \u2502       \u251c\u2500\u2500 fib(1) = 1")
        print("      \u2502       \u2514\u2500\u2500 fib(0) = 0")
        print("      \u2514\u2500\u2500 fib(3)")
        print("          \u251c\u2500\u2500 fib(2)")
        print("          \u2502   \u251c\u2500\u2500 fib(1) = 1")
        print("          \u2502   \u2514\u2500\u2500 fib(0) = 0")
        print("          \u2514\u2500\u2500 fib(1) = 1")
        print()
        print("    Counts: fib(0)=3, fib(1)=5, fib(2)=3, fib(3)=2, fib(4)=1, fib(5)=1")
        print("    Notice how the counts themselves follow a Fibonacci-like pattern!")
    else:
        print("  \u2717 B1: Call counts for fib_recursive(5) \u2014 FAIL")
        print(f"    Expected: {expected_counts}")
        print(f"    Got:      {counts}")
        print("    Hint: draw the full call tree on paper, starting from fib(5).")
    print()

    # -- B2: Total calls for fib_recursive(5) --
    total += 1
    total_calls_5 = total_calls_recursive_5()
    if total_calls_5 == 15:
        passed += 1
        print("  \u2713 B2: Total calls for fib_recursive(5) = 15 \u2014 PASS")
        print("    Sum of all nodes in the tree: 1+1+2+3+5+3 = 15")
    else:
        print("  \u2717 B2: Total calls for fib_recursive(5) \u2014 FAIL")
        print(f"    Expected: 15")
        print(f"    Got:      {total_calls_5}")
        print("    Hint: count every node in your call tree from B1.")
    print()

    # -- B3: Total calls for fib_recursive(10) --
    total += 1
    total_calls_10 = total_calls_recursive_10()
    if total_calls_10 == 177:
        passed += 1
        print("  \u2713 B3: Total calls for fib_recursive(10) = 177 \u2014 PASS")
        print("    The pattern: T(n) = 1 + T(n-1) + T(n-2)")
        print("    T(0)=1, T(1)=1, T(2)=3, T(3)=5, T(4)=9, T(5)=15,")
        print("    T(6)=25, T(7)=41, T(8)=67, T(9)=109, T(10)=177")
        print("    The call count itself grows exponentially!")
    else:
        print("  \u2717 B3: Total calls for fib_recursive(10) \u2014 FAIL")
        print(f"    Expected: 177")
        print(f"    Got:      {total_calls_10}")
        print("    Hint: T(n) = 1 + T(n-1) + T(n-2), with T(0)=1, T(1)=1.")
    print()

    # -- B4: Total calls for fib_memoized(5) --
    total += 1
    memo_calls_5 = total_calls_memoized_5()
    if memo_calls_5 == 9:
        passed += 1
        print("  \u2713 B4: Total calls for fib_memoized(5) = 9 \u2014 PASS")
        print("    With memoization, fib(5) still recurses into fib(4) and fib(3).")
        print("    But fib(3) was already computed during fib(4)'s recursion,")
        print("    so it returns from cache immediately. Only 9 calls total")
        print("    vs 15 without memoization. The savings grow dramatically")
        print("    for larger N (177 calls at N=10 drops to just 19).")
    else:
        print("  \u2717 B4: Total calls for fib_memoized(5) \u2014 FAIL")
        print(f"    Expected: 9")
        print(f"    Got:      {memo_calls_5}")
        print("    Hint: trace through the memoized version. fib(5) calls fib(4)+fib(3).")
        print("    fib(4) recurses fully (computing fib(3), fib(2), fib(1), fib(0)).")
        print("    Then fib(3) from fib(5) hits the cache and returns immediately.")
    print()

    # -- B5-B12: Complexity Questions --

    complexity_questions = [
        ("B5", "Time complexity of fib_recursive", time_complexity_recursive(), "O(2^N)",
         "Each call branches into TWO subcalls. The call tree is a binary tree\n"
         "    of depth N, so the number of calls is roughly 2^N.\n"
         "    (More precisely, it's O(phi^N) where phi = 1.618..., the golden ratio.)",
         "Hint: look at how the call count grew from B2 to B3."),

        ("B6", "Space complexity of fib_recursive", space_complexity_recursive(), "O(N)",
         "Even though there are 2^N calls, they don't all exist at once.\n"
         "    The deepest path in the call tree has N frames on the stack.\n"
         "    (fib(5) -> fib(4) -> fib(3) -> fib(2) -> fib(1) = 5 frames)",
         "Hint: how deep does the call stack get? Each call waits for\n"
         "    its left child to return before calling its right child."),

        ("B7", "Time complexity of fib_memoized", time_complexity_memoized(), "O(N)",
         "Each fib(k) for k in [0, N] is computed exactly once and cached.\n"
         "    Subsequent calls return in O(1). Total: N+1 unique computations = O(N).",
         "Hint: with memoization, how many UNIQUE fib(k) values are computed?"),

        ("B8", "Space complexity of fib_memoized", space_complexity_memoized(), "O(N)",
         "The memo dict has N+1 entries, and the call stack can be N deep.\n"
         "    Both are O(N), so total space is O(N).",
         "Hint: consider the memo dict size AND the call stack depth."),

        ("B9", "Time complexity of fib_bottom_up", time_complexity_bottom_up(), "O(N)",
         "A single loop from 2 to N, each iteration doing O(1) work.",
         "Hint: how many iterations does the loop do?"),

        ("B10", "Space complexity of fib_bottom_up", space_complexity_bottom_up(), "O(N)",
         "The dp list has N+1 entries = O(N) space.\n"
         "    No recursion, so no call stack overhead.",
         "Hint: how big is the dp list?"),

        ("B11", "Time complexity of fib_iterative", time_complexity_iterative(), "O(N)",
         "Same as bottom-up: one loop from 2 to N.",
         ""),

        ("B12", "Space complexity of fib_iterative", space_complexity_iterative(), "O(1)",
         "Only two variables (prev, curr) regardless of N.\n"
         "    This is the most space-efficient approach.",
         "Hint: how many variables does the loop use? Does it depend on N?"),
    ]

    for label, desc, student_answer, expected, feedback_pass, hint_fail in complexity_questions:
        total += 1
        normalized = _normalize(student_answer)
        if normalized == expected:
            passed += 1
            print(f"  \u2713 {label}: {desc} = {expected} \u2014 PASS")
            if feedback_pass:
                print(f"    {feedback_pass}")
        else:
            print(f"  \u2717 {label}: {desc} \u2014 FAIL")
            print(f"    Got: {student_answer}")
            if hint_fail:
                print(f"    {hint_fail}")
        print()

    # -- Summary --
    print(border)
    print(f"  Analysis: {passed} / {total} questions correct")
    print(border)

    return passed == total


# ===============================================================
#  Helpers
# ===============================================================

def _reference_fib(n):
    if n <= 1:
        return n
    prev, curr = 0, 1
    for _ in range(2, n + 1):
        prev, curr = curr, prev + curr
    return curr


def _make_random_case(rng, fib_recursive):
    n = rng.randint(0, 40)
    expected = _reference_fib(n)
    return Case(
        f"fib({n})",
        lambda n=n: fib_recursive(n),
        expected)


def _normalize(s):
    """Normalize complexity strings: strip, uppercase, remove spaces."""
    if s is None:
        return ""
    return s.strip().upper().replace(" ", "")
