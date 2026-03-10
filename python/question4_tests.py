"""
Test infrastructure for Problem 4 -- Factorial: Four Implementations + Analysis.
Contains reference solution, benchmarks, scaling analysis, correctness tests,
and analysis question checking with feedback.
"""

import random
import sys
from test_harness import TestHarness, Case

# Allow deep recursion for memoized factorial at large N
sys.setrecursionlimit(20_000)


# ===============================================================
#  PART A -- Code Implementation Tests
# ===============================================================

def build_code_harness(fact_recursive, fact_memoized, fact_bottom_up, fact_iterative):
    """Build a fully configured test harness for Problem 4 code implementations."""
    rng = random.Random(42)

    return TestHarness("Factorial \u2014 Four Implementations + Analysis") \
        \
        .add_test("Recursive: fact(0) = 1",
            lambda: fact_recursive(0), 1) \
        .add_test("Recursive: fact(1) = 1",
            lambda: fact_recursive(1), 1) \
        .add_test("Recursive: fact(2) = 2",
            lambda: fact_recursive(2), 2) \
        .add_test("Recursive: fact(5) = 120",
            lambda: fact_recursive(5), 120) \
        .add_test("Recursive: fact(10) = 3628800",
            lambda: fact_recursive(10), 3628800) \
        .add_test("Recursive: fact(15) = 1307674368000",
            lambda: fact_recursive(15), 1307674368000) \
        .add_test("Recursive: fact(20) = 2432902008176640000",
            lambda: fact_recursive(20), 2432902008176640000) \
        \
        .add_test("Memoized: fact(0) = 1",
            lambda: fact_memoized(0), 1) \
        .add_test("Memoized: fact(1) = 1",
            lambda: fact_memoized(1), 1) \
        .add_test("Memoized: fact(2) = 2",
            lambda: fact_memoized(2), 2) \
        .add_test("Memoized: fact(5) = 120",
            lambda: fact_memoized(5), 120) \
        .add_test("Memoized: fact(10) = 3628800",
            lambda: fact_memoized(10), 3628800) \
        .add_test("Memoized: fact(15) = 1307674368000",
            lambda: fact_memoized(15), 1307674368000) \
        .add_test("Memoized: fact(20) = 2432902008176640000",
            lambda: fact_memoized(20), 2432902008176640000) \
        \
        .add_test("Bottom-Up: fact(0) = 1",
            lambda: fact_bottom_up(0), 1) \
        .add_test("Bottom-Up: fact(1) = 1",
            lambda: fact_bottom_up(1), 1) \
        .add_test("Bottom-Up: fact(2) = 2",
            lambda: fact_bottom_up(2), 2) \
        .add_test("Bottom-Up: fact(5) = 120",
            lambda: fact_bottom_up(5), 120) \
        .add_test("Bottom-Up: fact(10) = 3628800",
            lambda: fact_bottom_up(10), 3628800) \
        .add_test("Bottom-Up: fact(15) = 1307674368000",
            lambda: fact_bottom_up(15), 1307674368000) \
        .add_test("Bottom-Up: fact(20) = 2432902008176640000",
            lambda: fact_bottom_up(20), 2432902008176640000) \
        \
        .add_test("Iterative: fact(0) = 1",
            lambda: fact_iterative(0), 1) \
        .add_test("Iterative: fact(1) = 1",
            lambda: fact_iterative(1), 1) \
        .add_test("Iterative: fact(2) = 2",
            lambda: fact_iterative(2), 2) \
        .add_test("Iterative: fact(5) = 120",
            lambda: fact_iterative(5), 120) \
        .add_test("Iterative: fact(10) = 3628800",
            lambda: fact_iterative(10), 3628800) \
        .add_test("Iterative: fact(15) = 1307674368000",
            lambda: fact_iterative(15), 1307674368000) \
        .add_test("Iterative: fact(20) = 2432902008176640000",
            lambda: fact_iterative(20), 2432902008176640000) \
        \
        .add_benchmark("Recursive N=20",
            lambda: fact_recursive(20)) \
        .add_benchmark("Memoized N=20",
            lambda: fact_memoized(20)) \
        .add_benchmark("Bottom-Up N=20",
            lambda: fact_bottom_up(20)) \
        .add_benchmark("Iterative N=20",
            lambda: fact_iterative(20)) \
        \
        .add_scaling("N (recursive)",
            [100, 500, 1_000, 5_000, 10_000],
            lambda n: n,
            lambda n: fact_recursive(n)) \
        .add_scaling("N (memoized)",
            [100, 500, 1_000, 5_000, 10_000],
            lambda n: n,
            lambda n: fact_memoized(n)) \
        .add_scaling("N (bottom-up)",
            [100, 500, 1_000, 5_000, 10_000],
            lambda n: n,
            lambda n: fact_bottom_up(n)) \
        .add_scaling("N (iterative)",
            [100, 500, 1_000, 5_000, 10_000],
            lambda n: n,
            lambda n: fact_iterative(n)) \
        \
        .add_random_tests("Recursive vs Reference (N in [0, 20])", 100,
            lambda: _make_random_case(rng, fact_recursive))


# ===============================================================
#  PART B -- Analysis Question Checking
# ===============================================================

def run_analysis():
    """Check all 12 analysis questions and provide feedback."""
    # Import analysis functions from the student file
    from question4_factorial import (
        call_counts_factorial_5, total_calls_recursive_5, total_calls_recursive_10,
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

    # -- B1: Call counts for fact_recursive(5) --
    total += 1
    counts = call_counts_factorial_5()
    expected_counts = [1, 1, 1, 1, 1, 1]
    if counts is not None and list(counts) == expected_counts:
        passed += 1
        print("  \u2713 B1: Call counts for fact_recursive(5) \u2014 PASS")
        print()
        print("    Here's the call tree for factorial(5):")
        print()
        print("      fact(5)")
        print("      \u2514\u2500\u2500 fact(4)")
        print("          \u2514\u2500\u2500 fact(3)")
        print("              \u2514\u2500\u2500 fact(2)")
        print("                  \u2514\u2500\u2500 fact(1)")
        print("                      \u2514\u2500\u2500 fact(0) = 1")
        print()
        print("    Each fact(k) is called exactly once \u2014 a straight line!")
        print("    Unlike Fibonacci's branching tree, factorial has NO overlapping")
        print("    subproblems. The call tree has N+1 nodes, not 2^N.")
    else:
        print("  \u2717 B1: Call counts for fact_recursive(5) \u2014 FAIL")
        print(f"    Expected: {expected_counts}")
        print(f"    Got:      {counts}")
        print("    Hint: draw the call tree on paper. fact(5) calls fact(4),")
        print("    which calls fact(3), and so on. It's a straight line!")
    print()

    # -- B2: Total calls for fact_recursive(5) --
    total += 1
    total_calls_5 = total_calls_recursive_5()
    if total_calls_5 == 6:
        passed += 1
        print("  \u2713 B2: Total calls for fact_recursive(5) = 6 \u2014 PASS")
        print("    fact(5) \u2192 fact(4) \u2192 fact(3) \u2192 fact(2) \u2192 fact(1) \u2192 fact(0)")
        print("    That's 6 calls total: one for each value from 5 down to 0.")
    else:
        print("  \u2717 B2: Total calls for fact_recursive(5) \u2014 FAIL")
        print(f"    Expected: 6")
        print(f"    Got:      {total_calls_5}")
        print("    Hint: count every node in the call tree from B1.")
    print()

    # -- B3: Total calls for fact_recursive(10) --
    total += 1
    total_calls_10 = total_calls_recursive_10()
    if total_calls_10 == 11:
        passed += 1
        print("  \u2713 B3: Total calls for fact_recursive(10) = 11 \u2014 PASS")
        print("    The pattern: T(n) = n + 1")
        print("    T(0)=1, T(1)=2, T(2)=3, ..., T(10)=11")
        print("    Each call makes exactly one recursive call, so it's linear.")
    else:
        print("  \u2717 B3: Total calls for fact_recursive(10) \u2014 FAIL")
        print(f"    Expected: 11")
        print(f"    Got:      {total_calls_10}")
        print("    Hint: T(n) = 1 + T(n-1), with T(0)=1. So T(n) = n + 1.")
    print()

    # -- B4: Total calls for fact_memoized(5) --
    total += 1
    memo_calls_5 = total_calls_memoized_5()
    if memo_calls_5 == 6:
        passed += 1
        print("  \u2713 B4: Total calls for fact_memoized(5) = 6 \u2014 PASS")
        print("    6 calls \u2014 exactly the same as without memoization!")
        print("    Since each fact(k) is already called only once, there's")
        print("    nothing to cache. Memoization adds overhead with no benefit.")
        print("    This is the key contrast with Fibonacci.")
    else:
        print("  \u2717 B4: Total calls for fact_memoized(5) \u2014 FAIL")
        print(f"    Expected: 6")
        print(f"    Got:      {memo_calls_5}")
        print("    Hint: since each fact(k) is already called only once in the")
        print("    recursive version, memoization doesn't reduce any calls.")
    print()

    # -- B5-B12: Complexity Questions --

    complexity_questions = [
        ("B5", "Time complexity of fact_recursive", time_complexity_recursive(), "O(N)",
         "Only N+1 calls, each doing O(1) work. NOT exponential like Fibonacci!",
         "Hint: how many calls does fact_recursive(n) make total?"),

        ("B6", "Space complexity of fact_recursive", space_complexity_recursive(), "O(N)",
         "The call stack goes N levels deep.",
         "Hint: how deep does the call stack get?"),

        ("B7", "Time complexity of fact_memoized", time_complexity_memoized(), "O(N)",
         "Same as recursive \u2014 memoization doesn't change the work here.",
         "Hint: does memoization reduce the number of calls for factorial?"),

        ("B8", "Space complexity of fact_memoized", space_complexity_memoized(), "O(N)",
         "The memo dict has N+1 entries, and the call stack is N deep.\n"
         "    Both are O(N), so total space is O(N).",
         "Hint: consider the memo dict size AND the call stack depth."),

        ("B9", "Time complexity of fact_bottom_up", time_complexity_bottom_up(), "O(N)",
         "A single loop from 1 to N, each iteration doing O(1) work.",
         "Hint: how many iterations does the loop do?"),

        ("B10", "Space complexity of fact_bottom_up", space_complexity_bottom_up(), "O(N)",
         "The dp list has N+1 entries = O(N) space.\n"
         "    No recursion, so no call stack overhead.",
         "Hint: how big is the dp list?"),

        ("B11", "Time complexity of fact_iterative", time_complexity_iterative(), "O(N)",
         "Same as bottom-up: one loop from 1 to N.",
         ""),

        ("B12", "Space complexity of fact_iterative", space_complexity_iterative(), "O(1)",
         "Only one accumulator variable regardless of N.",
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

def _reference_fact(n):
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result


def _make_random_case(rng, fact_recursive):
    n = rng.randint(0, 20)
    expected = _reference_fact(n)
    return Case(
        f"fact({n})",
        lambda n=n: fact_recursive(n),
        expected)


def _normalize(s):
    """Normalize complexity strings: strip, uppercase, remove spaces."""
    if s is None:
        return ""
    return s.strip().upper().replace(" ", "")
