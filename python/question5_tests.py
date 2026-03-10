"""
Test infrastructure for Problem 4 -- Climbing Stairs: Three Implementations.
Contains reference solution, benchmarks, scaling analysis, and all test cases.
"""

import random
import sys
from test_harness import TestHarness, Case

# Allow deep recursion for memoized climbing stairs at large N
sys.setrecursionlimit(20_000)


def build_harness(solve_recursive, solve_memoized, solve_iterative):
    """Build a fully configured test harness for Problem 4."""
    rng = random.Random(42)

    return (
        TestHarness("Climbing Stairs \u2014 Three Implementations")

        .add_test("Recursive: climb(1) = 1",
            lambda: solve_recursive(1), 1)
        .add_test("Recursive: climb(2) = 2",
            lambda: solve_recursive(2), 2)
        .add_test("Recursive: climb(3) = 3",
            lambda: solve_recursive(3), 3)
        .add_test("Recursive: climb(5) = 8",
            lambda: solve_recursive(5), 8)
        .add_test("Recursive: climb(10) = 89",
            lambda: solve_recursive(10), 89)
        .add_test("Recursive: climb(20) = 10946",
            lambda: solve_recursive(20), 10946)

        .add_test("Memoized: climb(1) = 1",
            lambda: solve_memoized(1), 1)
        .add_test("Memoized: climb(2) = 2",
            lambda: solve_memoized(2), 2)
        .add_test("Memoized: climb(5) = 8",
            lambda: solve_memoized(5), 8)
        .add_test("Memoized: climb(10) = 89",
            lambda: solve_memoized(10), 89)
        .add_test("Memoized: climb(20) = 10946",
            lambda: solve_memoized(20), 10946)
        .add_test("Memoized: climb(45) = 1836311903",
            lambda: solve_memoized(45), 1836311903)

        .add_test("Iterative: climb(1) = 1",
            lambda: solve_iterative(1), 1)
        .add_test("Iterative: climb(2) = 2",
            lambda: solve_iterative(2), 2)
        .add_test("Iterative: climb(5) = 8",
            lambda: solve_iterative(5), 8)
        .add_test("Iterative: climb(10) = 89",
            lambda: solve_iterative(10), 89)
        .add_test("Iterative: climb(20) = 10946",
            lambda: solve_iterative(20), 10946)
        .add_test("Iterative: climb(45) = 1836311903",
            lambda: solve_iterative(45), 1836311903)

        .add_benchmark("Recursive N=30",
            lambda: solve_recursive(30))
        .add_benchmark("Memoized N=30",
            lambda: solve_memoized(30))
        .add_benchmark("Iterative N=30",
            lambda: solve_iterative(30))

        .add_scaling("N (memoized)",
            [100, 500, 1_000, 5_000, 10_000],
            lambda n: n,
            lambda n: solve_memoized(n))
        .add_scaling("N (iterative)",
            [100, 500, 1_000, 5_000, 10_000],
            lambda n: n,
            lambda n: solve_iterative(n))

        .add_random_tests("Recursive vs Reference (N=1..25)", 100,
            lambda: _make_random_case(rng, solve_recursive))
    )


# -- Reference solution -------------------------------------------

def _reference(n):
    if n <= 1:
        return 1
    prev, curr = 1, 2
    for _ in range(3, n + 1):
        prev, curr = curr, prev + curr
    return curr


# -- Random case generator ----------------------------------------

def _make_random_case(rng, solve_recursive):
    n = rng.randint(1, 25)
    expected = _reference(n)
    return Case(
        f"climb({n})",
        lambda n=n: solve_recursive(n),
        expected)
