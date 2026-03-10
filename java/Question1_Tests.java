import java.util.*;
import java.util.function.*;

public class Question1_Tests {

    private static int[] genKeys(int n) {
        Random gen = new Random(42);
        int[] keys = new int[n];
        for (int i = 0; i < n; i++) {
            keys[i] = gen.nextInt(n * 10);
        }
        return keys;
    }

    public static TestHarness<Boolean> buildHarness() {
        Random rng = new Random(42);

        return TestHarness.<Boolean>forProblem("Custom HashMap (Open Addressing)")

            // ── Correctness tests ───────────────────────────

            .addTest("Basic put/get", () -> {
                MyHashMap m = new MyHashMap();
                m.put(1, 100);
                m.put(2, 200);
                m.put(3, 300);
                return m.get(1) == 100 && m.get(2) == 200 && m.get(3) == 300;
            }, true)

            .addTest("Get missing key returns -1", () -> {
                MyHashMap m = new MyHashMap();
                m.put(1, 100);
                return m.get(999) == -1 && m.get(0) == -1;
            }, true)

            .addTest("Overwrite value", () -> {
                MyHashMap m = new MyHashMap();
                m.put(1, 100);
                m.put(1, 999);
                return m.get(1) == 999;
            }, true)

            .addTest("containsKey true/false", () -> {
                MyHashMap m = new MyHashMap();
                m.put(42, 1);
                return m.containsKey(42) && !m.containsKey(99);
            }, true)

            .addTest("Remove existing key", () -> {
                MyHashMap m = new MyHashMap();
                m.put(5, 50);
                boolean removed = m.remove(5);
                return removed && m.get(5) == -1 && !m.containsKey(5);
            }, true)

            .addTest("Remove non-existent key returns false", () -> {
                MyHashMap m = new MyHashMap();
                m.put(1, 10);
                return !m.remove(42);
            }, true)

            .addTest("Tombstone recovery: remove then re-put", () -> {
                MyHashMap m = new MyHashMap();
                m.put(5, 50);
                m.remove(5);
                m.put(5, 999);
                return m.get(5) == 999 && m.containsKey(5) && m.size() == 1;
            }, true)

            .addTest("Triggers resize (more than initial capacity)", () -> {
                MyHashMap m = new MyHashMap();
                // Insert well past the initial capacity of 16
                for (int i = 0; i < 50; i++) {
                    m.put(i * 37, i);
                }
                for (int i = 0; i < 50; i++) {
                    if (m.get(i * 37) != i) {
                        return false;
                    }
                }
                return m.size() == 50;
            }, true)

            .addTest("Negative keys", () -> {
                MyHashMap m = new MyHashMap();
                m.put(-1, 10);
                m.put(-100, 20);
                m.put(Integer.MIN_VALUE, 30);
                return m.get(-1) == 10
                    && m.get(-100) == 20
                    && m.get(Integer.MIN_VALUE) == 30
                    && m.containsKey(-1);
            }, true)

            .addTest("Size accuracy (put 5, remove 2)", () -> {
                MyHashMap m = new MyHashMap();
                for (int i = 0; i < 5; i++) {
                    m.put(i, i * 10);
                }
                m.remove(1);
                m.remove(3);
                return m.size() == 3;
            }, true)

            .addTest("Resize after removals preserves data", () -> {
                MyHashMap m = new MyHashMap();
                for (int i = 0; i < 20; i++) {
                    m.put(i, i * 10);
                }
                for (int i = 0; i < 5; i++) {
                    m.remove(i);
                }
                // Add more to trigger further resizing
                for (int i = 20; i < 50; i++) {
                    m.put(i, i * 10);
                }
                if (m.size() != 45) {
                    return false;
                }
                for (int i = 5; i < 50; i++) {
                    if (m.get(i) != i * 10) {
                        return false;
                    }
                }
                return true;
            }, true)

            .addTest("1000 entries: put then get all", () -> {
                MyHashMap m = new MyHashMap();
                for (int i = 0; i < 1000; i++) {
                    m.put(i, i * 7);
                }
                for (int i = 0; i < 1000; i++) {
                    if (m.get(i) != i * 7) {
                        return false;
                    }
                }
                return m.size() == 1000;
            }, true)

            // ── Benchmark ───────────────────────────────────

            .addBenchmark("100,000 put + get operations", () -> {
                MyHashMap m = new MyHashMap();
                for (int i = 0; i < 100_000; i++) {
                    m.put(i, i);
                }
                int sum = 0;
                for (int i = 0; i < 100_000; i++) {
                    sum += m.get(i);
                }
                return sum > 0;
            })

            // ── Scaling analysis ────────────────────────────

            .addScaling("N (put + get operations)",
                new int[]{1_000, 5_000, 10_000, 50_000, 100_000},
                n -> genKeys(n),
                (int[] input) -> {
                    MyHashMap m = new MyHashMap();
                    for (int k : input) {
                        m.put(k, k);
                    }
                    for (int k : input) {
                        m.get(k);
                    }
                    return true;
                })

            // ── Random stress tests ─────────────────────────

            .addRandomTests("vs java.util.HashMap", 1000, () -> {
                int numOps = 20 + rng.nextInt(31);
                int[] opTypes = new int[numOps];
                int[] opKeys = new int[numOps];
                int[] opVals = new int[numOps];
                for (int i = 0; i < numOps; i++) {
                    opTypes[i] = rng.nextInt(5);
                    opKeys[i] = rng.nextInt(200) - 50;
                    opVals[i] = rng.nextInt(1000);
                }

                // Compute reference results using java.util.HashMap
                HashMap<Integer, Integer> ref = new HashMap<>();
                int[] refGet = new int[numOps];
                boolean[] refBool = new boolean[numOps];
                int[] refSize = new int[numOps];
                for (int i = 0; i < numOps; i++) {
                    switch (opTypes[i]) {
                        case 0:
                            ref.put(opKeys[i], opVals[i]);
                            break;
                        case 1:
                            refGet[i] = ref.getOrDefault(opKeys[i], -1);
                            break;
                        case 2:
                            refBool[i] = ref.remove(opKeys[i]) != null;
                            break;
                        case 3:
                            refBool[i] = ref.containsKey(opKeys[i]);
                            break;
                        case 4:
                            refSize[i] = ref.size();
                            break;
                    }
                }

                return new TestHarness.Case<>(
                    numOps + " random ops",
                    () -> {
                        MyHashMap m = new MyHashMap();
                        for (int i = 0; i < numOps; i++) {
                            switch (opTypes[i]) {
                                case 0:
                                    m.put(opKeys[i], opVals[i]);
                                    break;
                                case 1:
                                    if (m.get(opKeys[i]) != refGet[i]) {
                                        return false;
                                    }
                                    break;
                                case 2:
                                    if (m.remove(opKeys[i]) != refBool[i]) {
                                        return false;
                                    }
                                    break;
                                case 3:
                                    if (m.containsKey(opKeys[i]) != refBool[i]) {
                                        return false;
                                    }
                                    break;
                                case 4:
                                    if (m.size() != refSize[i]) {
                                        return false;
                                    }
                                    break;
                            }
                        }
                        return true;
                    },
                    true
                );
            });
    }
}
