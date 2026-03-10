"""
Test infrastructure for Problem 3 -- Coin Combination Amounts: Three Implementations.
Contains reference solution, benchmarks, scaling analysis, and all test cases.
"""

import random
from test_harness import TestHarness, Case


def build_harness(solve_recursive, solve_memoized, solve_iterative):
    """Build a fully configured test harness for Problem 3."""
    rng = random.Random(42)

    return TestHarness("Coin Combination Amounts \u2014 Three Implementations") \
        \
        .add_test("Recursive: solve(0) = 1",
            lambda: solve_recursive(0), 1) \
        .add_test("Recursive: solve(1) = 5",
            lambda: solve_recursive(1), 5) \
        .add_test("Recursive: solve(2) = 14",
            lambda: solve_recursive(2), 14) \
        .add_test("Recursive: solve(3)",
            lambda: solve_recursive(3), _brute(3)) \
        .add_test("Recursive: solve(5)",
            lambda: solve_recursive(5), _brute(5)) \
        \
        .add_test("Memoized: solve(0) = 1",
            lambda: solve_memoized(0), 1) \
        .add_test("Memoized: solve(1) = 5",
            lambda: solve_memoized(1), 5) \
        .add_test("Memoized: solve(2) = 14",
            lambda: solve_memoized(2), 14) \
        .add_test("Memoized: solve(5)",
            lambda: solve_memoized(5), _brute(5)) \
        .add_test("Memoized: solve(10)",
            lambda: solve_memoized(10), _brute(10)) \
        \
        .add_test("Iterative: solve(0) = 1",
            lambda: solve_iterative(0), 1) \
        .add_test("Iterative: solve(1) = 5",
            lambda: solve_iterative(1), 5) \
        .add_test("Iterative: solve(2) = 14",
            lambda: solve_iterative(2), 14) \
        .add_test("Iterative: solve(5)",
            lambda: solve_iterative(5), _brute(5)) \
        .add_test("Iterative: solve(10)",
            lambda: solve_iterative(10), _brute(10)) \
        \
        .add_benchmark("Recursive N=5",
            lambda: solve_recursive(5)) \
        .add_benchmark("Memoized N=50",
            lambda: solve_memoized(50)) \
        .add_benchmark("Iterative N=100",
            lambda: solve_iterative(100)) \
        \
        .add_scaling("N (memoized)",
            [10, 25, 50, 100, 200],
            lambda n: n,
            lambda n: solve_memoized(n)) \
        .add_scaling("N (iterative)",
            [10, 25, 50, 100, 200],
            lambda n: n,
            lambda n: solve_iterative(n)) \
        \
        .add_random_tests("Recursive vs Reference (N=0..8)", 100,
            lambda: _make_random_case(rng, solve_recursive))


# -- Reference solution -----------------------------------

def _brute(n):
    reachable = {0}
    coins = [1, 5, 10, 25]
    for step in range(n):
        next_set = set(reachable)
        for amt in reachable:
            for c in coins:
                next_set.add(amt + c)
        reachable = next_set
    return len(reachable)


# -- Random case generator --------------------------------

def _make_random_case(rng, solve_recursive):
    n = rng.randint(0, 8)
    expected = _brute(n)
    return Case(
        f"N={n}",
        lambda n=n: solve_recursive(n),
        expected)
