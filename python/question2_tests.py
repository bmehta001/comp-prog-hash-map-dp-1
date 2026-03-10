import random
from test_harness import TestHarness, Case


def build_harness(linked_list_class):
    """Build a test harness for the custom LinkedList implementation."""

    def _new():
        return linked_list_class()

    # ── Correctness tests ────────────────────────────────

    def test_add_and_size():
        ll = _new()
        for i in range(5):
            ll.add(i * 10)
        return ll.size() == 5

    def test_get_elements():
        ll = _new()
        ll.add(10)
        ll.add(20)
        ll.add(30)
        return ll.get(0) == 10 and ll.get(1) == 20 and ll.get(2) == 30

    def test_remove_first():
        ll = _new()
        ll.add(1)
        ll.add(2)
        ll.add(3)
        removed = ll.remove(0)
        return removed == 1 and ll.size() == 2 and ll.get(0) == 2

    def test_remove_last():
        ll = _new()
        ll.add(1)
        ll.add(2)
        ll.add(3)
        removed = ll.remove(2)
        return removed == 3 and ll.size() == 2

    def test_remove_middle():
        ll = _new()
        ll.add(1)
        ll.add(2)
        ll.add(3)
        removed = ll.remove(1)
        return removed == 2 and ll.get(0) == 1 and ll.get(1) == 3

    def test_contains_true():
        ll = _new()
        ll.add(5)
        ll.add(10)
        ll.add(15)
        return ll.contains(10)

    def test_contains_false():
        ll = _new()
        ll.add(5)
        ll.add(10)
        ll.add(15)
        return not ll.contains(20)

    def test_reverse_list():
        ll = _new()
        for i in range(1, 6):
            ll.add(i)
        ll.reverse()
        return (ll.get(0) == 5
                and ll.get(1) == 4
                and ll.get(2) == 3
                and ll.get(3) == 2
                and ll.get(4) == 1)

    def test_reverse_single():
        ll = _new()
        ll.add(42)
        ll.reverse()
        return ll.get(0) == 42 and ll.size() == 1

    def test_reverse_empty():
        ll = _new()
        ll.reverse()
        return ll.size() == 0

    def test_empty_size():
        ll = _new()
        return ll.size() == 0

    def test_get_out_of_bounds():
        ll = _new()
        ll.add(1)
        try:
            ll.get(-1)
            return False
        except IndexError:
            pass
        try:
            ll.get(1)
            return False
        except IndexError:
            pass
        # Also test on empty list
        empty = _new()
        try:
            empty.get(0)
            return False
        except IndexError:
            pass
        return True

    def test_remove_out_of_bounds():
        ll = _new()
        ll.add(1)
        ll.add(2)
        ll.add(3)
        try:
            ll.remove(5)
            return False
        except IndexError:
            pass
        try:
            ll.remove(-1)
            return False
        except IndexError:
            pass
        return True

    # ── Benchmark helper ─────────────────────────────────

    def bench_add_and_get():
        ll = _new()
        for i in range(10_000):
            ll.add(i)
        bench_rng = random.Random(42)
        total = 0
        for _ in range(1_000):
            total += ll.get(bench_rng.randint(0, ll.size() - 1))
        return total != -(10 ** 18)

    # ── Scaling helper ───────────────────────────────────

    def solve_scaling(n):
        ll = _new()
        for i in range(n):
            ll.add(i)
        return ll.size() > 0

    # ── Random stress test generator ─────────────────────

    rng = random.Random(42)

    def case_generator():
        num_ops = rng.randint(20, 50)
        ops = []
        for _ in range(num_ops):
            op_type = rng.randint(0, 4)
            arg = rng.randint(-50, 149)
            ops.append((op_type, arg))

        # Compute reference results using built-in list
        ref = []
        ref_results = []
        for op_type, arg in ops:
            if op_type == 0:
                # add
                ref.append(arg)
                ref_results.append(("add", None))
            elif op_type == 1:
                # get (only if non-empty)
                if not ref:
                    ref_results.append(("skip", None))
                else:
                    idx = abs(arg) % len(ref)
                    ref_results.append(("get", ref[idx]))
            elif op_type == 2:
                # remove (only if non-empty)
                if not ref:
                    ref_results.append(("skip", None))
                else:
                    idx = abs(arg) % len(ref)
                    val = ref.pop(idx)
                    ref_results.append(("remove", val))
            elif op_type == 3:
                # contains
                ref_results.append(("contains", arg in ref))
            elif op_type == 4:
                # size
                ref_results.append(("size", len(ref)))

        ops_snapshot = list(ops)
        ref_snapshot = list(ref_results)

        def fn():
            ll = _new()
            for i, (op_type, arg) in enumerate(ops_snapshot):
                kind, expected = ref_snapshot[i]
                if kind == "skip":
                    continue
                if op_type == 0:
                    ll.add(arg)
                elif op_type == 1:
                    idx = abs(arg) % max(ll.size(), 1)
                    if ll.get(idx) != expected:
                        return False
                elif op_type == 2:
                    idx = abs(arg) % max(ll.size(), 1)
                    if ll.remove(idx) != expected:
                        return False
                elif op_type == 3:
                    if ll.contains(arg) != expected:
                        return False
                elif op_type == 4:
                    if ll.size() != expected:
                        return False
            return True

        return Case(f"{num_ops} random ops", fn, True)

    # ── Build harness ────────────────────────────────────

    return TestHarness("Custom Linked List") \
        .add_test("add_and_size", test_add_and_size, True) \
        .add_test("get_elements", test_get_elements, True) \
        .add_test("remove_first", test_remove_first, True) \
        .add_test("remove_last", test_remove_last, True) \
        .add_test("remove_middle", test_remove_middle, True) \
        .add_test("contains_true", test_contains_true, True) \
        .add_test("contains_false", test_contains_false, True) \
        .add_test("reverse_list", test_reverse_list, True) \
        .add_test("reverse_single", test_reverse_single, True) \
        .add_test("reverse_empty", test_reverse_empty, True) \
        .add_test("empty_size", test_empty_size, True) \
        .add_test("get_out_of_bounds", test_get_out_of_bounds, True) \
        .add_test("remove_out_of_bounds", test_remove_out_of_bounds, True) \
        .add_benchmark("10,000 add + 1,000 random get", bench_add_and_get) \
        .add_scaling("N (add operations)",
                     [100, 500, 1_000, 5_000, 10_000],
                     lambda n: n, solve_scaling) \
        .add_random_tests("vs built-in list", 1000, case_generator)
