import random
from test_harness import TestHarness, Case


def build_harness(hash_map_class):
    """Build a test harness for the custom HashMap implementation."""

    def _new():
        return hash_map_class()

    # -- Correctness tests ------------------------------------

    def test_basic_put_get():
        m = _new()
        m.put(1, 100)
        m.put(2, 200)
        m.put(3, 300)
        return m.get(1) == 100 and m.get(2) == 200 and m.get(3) == 300

    def test_get_missing():
        m = _new()
        m.put(1, 100)
        return m.get(999) == -1 and m.get(0) == -1

    def test_overwrite():
        m = _new()
        m.put(1, 100)
        m.put(1, 999)
        return m.get(1) == 999

    def test_contains_key():
        m = _new()
        m.put(42, 1)
        return m.contains_key(42) and not m.contains_key(99)

    def test_remove_existing():
        m = _new()
        m.put(5, 50)
        removed = m.remove(5)
        return removed and m.get(5) == -1 and not m.contains_key(5)

    def test_remove_non_existent():
        m = _new()
        m.put(1, 10)
        return not m.remove(42)

    def test_tombstone_recovery():
        m = _new()
        m.put(5, 50)
        m.remove(5)
        m.put(5, 999)
        return m.get(5) == 999 and m.contains_key(5) and m.size() == 1

    def test_triggers_resize():
        m = _new()
        for i in range(50):
            m.put(i * 37, i)
        for i in range(50):
            if m.get(i * 37) != i:
                return False
        return m.size() == 50

    def test_negative_keys():
        m = _new()
        m.put(-1, 10)
        m.put(-100, 20)
        m.put(-2147483648, 30)
        return (m.get(-1) == 10
                and m.get(-100) == 20
                and m.get(-2147483648) == 30
                and m.contains_key(-1))

    def test_size_accuracy():
        m = _new()
        for i in range(5):
            m.put(i, i * 10)
        m.remove(1)
        m.remove(3)
        return m.size() == 3

    def test_resize_after_removals():
        m = _new()
        for i in range(20):
            m.put(i, i * 10)
        for i in range(5):
            m.remove(i)
        for i in range(20, 50):
            m.put(i, i * 10)
        if m.size() != 45:
            return False
        for i in range(5, 50):
            if m.get(i) != i * 10:
                return False
        return True

    def test_many_entries():
        m = _new()
        for i in range(1000):
            m.put(i, i * 7)
        for i in range(1000):
            if m.get(i) != i * 7:
                return False
        return m.size() == 1000

    # -- Benchmark helper -------------------------------------

    def bench_100k():
        m = _new()
        for i in range(100_000):
            m.put(i, i)
        total = 0
        for i in range(100_000):
            total += m.get(i)
        return total > 0

    # -- Scaling helper ---------------------------------------

    def gen_keys(n):
        gen = random.Random(42)
        return [gen.randint(0, n * 10) for _ in range(n)]

    def solve_scaling(keys):
        m = _new()
        for k in keys:
            m.put(k, k)
        for k in keys:
            m.get(k)
        return True

    # -- Random stress test generator -------------------------

    rng = random.Random(42)

    def case_generator():
        num_ops = rng.randint(20, 50)
        ops = []
        for _ in range(num_ops):
            op_type = rng.randint(0, 4)
            key = rng.randint(-50, 149)
            value = rng.randint(0, 999)
            ops.append((op_type, key, value))

        # Compute reference results using built-in dict
        ref = {}
        expected_results = []
        for op_type, key, value in ops:
            if op_type == 0:
                ref[key] = value
                expected_results.append(None)
            elif op_type == 1:
                expected_results.append(ref.get(key, -1))
            elif op_type == 2:
                was_present = key in ref
                if was_present:
                    del ref[key]
                expected_results.append(was_present)
            elif op_type == 3:
                expected_results.append(key in ref)
            elif op_type == 4:
                expected_results.append(len(ref))

        ops_snapshot = list(ops)
        exp_snapshot = list(expected_results)

        def fn():
            m = _new()
            for i, (op_type, key, value) in enumerate(ops_snapshot):
                if op_type == 0:
                    m.put(key, value)
                elif op_type == 1:
                    if m.get(key) != exp_snapshot[i]:
                        return False
                elif op_type == 2:
                    if m.remove(key) != exp_snapshot[i]:
                        return False
                elif op_type == 3:
                    if m.contains_key(key) != exp_snapshot[i]:
                        return False
                elif op_type == 4:
                    if m.size() != exp_snapshot[i]:
                        return False
            return True

        return Case(f"{num_ops} random ops", fn, True)

    # -- Build harness ----------------------------------------

    return TestHarness("Custom HashMap (Open Addressing)") \
        .add_test("Basic put/get", test_basic_put_get, True) \
        .add_test("Get missing key returns -1", test_get_missing, True) \
        .add_test("Overwrite value", test_overwrite, True) \
        .add_test("containsKey true/false", test_contains_key, True) \
        .add_test("Remove existing key", test_remove_existing, True) \
        .add_test("Remove non-existent key returns false", test_remove_non_existent, True) \
        .add_test("Tombstone recovery: remove then re-put", test_tombstone_recovery, True) \
        .add_test("Triggers resize (more than initial capacity)", test_triggers_resize, True) \
        .add_test("Negative keys", test_negative_keys, True) \
        .add_test("Size accuracy (put 5, remove 2)", test_size_accuracy, True) \
        .add_test("Resize after removals preserves data", test_resize_after_removals, True) \
        .add_test("1000 entries: put then get all", test_many_entries, True) \
        .add_benchmark("100,000 put + get operations", bench_100k) \
        .add_scaling("N (put + get operations)",
                     [1_000, 5_000, 10_000, 50_000, 100_000],
                     gen_keys, solve_scaling) \
        .add_random_tests("vs built-in dict", 1000, case_generator)
