/**
 * Test infrastructure for Question 1 — Custom HashMap (Open Addressing).
 *
 * NOTE: This header must be included AFTER both "test_harness.h" and the
 * MyHashMap class definition. It references MyHashMap directly.
 */
#pragma once

#include <climits>
#include <random>
#include <unordered_map>
#include <vector>

namespace q1_tests {

inline harness::TestHarness<bool> newHarness() {
    return harness::TestHarness<bool>::forProblem("Custom HashMap (Open Addressing)");
}

inline std::vector<int> genKeys(int n) {
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(0, n * 10);
    std::vector<int> keys(n);
    for (int i = 0; i < n; i++) {
        keys[i] = dist(gen);
    }
    return keys;
}

inline harness::TestHarness<bool>& addTests(harness::TestHarness<bool>& h) {

    // -- Correctness tests -----------------------------------

    h.addTest("Basic put/get", []() {
        MyHashMap m;
        m.put(1, 100);
        m.put(2, 200);
        m.put(3, 300);
        return m.get(1) == 100 && m.get(2) == 200 && m.get(3) == 300;
    }, true);

    h.addTest("Get missing key returns -1", []() {
        MyHashMap m;
        m.put(1, 100);
        return m.get(999) == -1 && m.get(0) == -1;
    }, true);

    h.addTest("Overwrite value", []() {
        MyHashMap m;
        m.put(1, 100);
        m.put(1, 999);
        return m.get(1) == 999;
    }, true);

    h.addTest("containsKey true/false", []() {
        MyHashMap m;
        m.put(42, 1);
        return m.containsKey(42) && !m.containsKey(99);
    }, true);

    h.addTest("Remove existing key", []() {
        MyHashMap m;
        m.put(5, 50);
        bool removed = m.remove(5);
        return removed && m.get(5) == -1 && !m.containsKey(5);
    }, true);

    h.addTest("Remove non-existent key returns false", []() {
        MyHashMap m;
        m.put(1, 10);
        return !m.remove(42);
    }, true);

    h.addTest("Tombstone recovery: remove then re-put", []() {
        MyHashMap m;
        m.put(5, 50);
        m.remove(5);
        m.put(5, 999);
        return m.get(5) == 999 && m.containsKey(5) && m.size() == 1;
    }, true);

    h.addTest("Triggers resize (more than initial capacity)", []() {
        MyHashMap m;
        for (int i = 0; i < 50; i++) {
            m.put(i * 37, i);
        }
        for (int i = 0; i < 50; i++) {
            if (m.get(i * 37) != i) {
                return false;
            }
        }
        return m.size() == 50;
    }, true);

    h.addTest("Negative keys", []() {
        MyHashMap m;
        m.put(-1, 10);
        m.put(-100, 20);
        m.put(INT_MIN, 30);
        return m.get(-1) == 10
            && m.get(-100) == 20
            && m.get(INT_MIN) == 30
            && m.containsKey(-1);
    }, true);

    h.addTest("Size accuracy (put 5, remove 2)", []() {
        MyHashMap m;
        for (int i = 0; i < 5; i++) {
            m.put(i, i * 10);
        }
        m.remove(1);
        m.remove(3);
        return m.size() == 3;
    }, true);

    h.addTest("Resize after removals preserves data", []() {
        MyHashMap m;
        for (int i = 0; i < 20; i++) {
            m.put(i, i * 10);
        }
        for (int i = 0; i < 5; i++) {
            m.remove(i);
        }
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
    }, true);

    h.addTest("1000 entries: put then get all", []() {
        MyHashMap m;
        for (int i = 0; i < 1000; i++) {
            m.put(i, i * 7);
        }
        for (int i = 0; i < 1000; i++) {
            if (m.get(i) != i * 7) {
                return false;
            }
        }
        return m.size() == 1000;
    }, true);

    // -- Benchmark -------------------------------------------

    h.addBenchmark("100,000 put + get operations", []() {
        MyHashMap m;
        for (int i = 0; i < 100000; i++) {
            m.put(i, i);
        }
        int sum = 0;
        for (int i = 0; i < 100000; i++) {
            sum += m.get(i);
        }
        return sum > 0;
    });

    // -- Scaling analysis ------------------------------------

    h.addScaling<std::vector<int>>(
        "N (put + get operations)",
        {1000, 5000, 10000, 50000, 100000},
        std::function<std::vector<int>(int)>([](int n) -> std::vector<int> {
            return genKeys(n);
        }),
        std::function<bool(const std::vector<int>&)>([](const std::vector<int>& input) -> bool {
            MyHashMap m;
            for (int k : input) {
                m.put(k, k);
            }
            for (int k : input) {
                m.get(k);
            }
            return true;
        })
    );

    // -- Random stress tests ---------------------------------

    static std::mt19937 rng(42);

    h.addRandomTests("vs std::unordered_map", 1000, []() -> harness::Case<bool> {
        std::uniform_int_distribution<int> numOpsDist(20, 50);
        std::uniform_int_distribution<int> opDist(0, 4);
        std::uniform_int_distribution<int> keyDist(-50, 149);
        std::uniform_int_distribution<int> valDist(0, 999);

        int numOps = numOpsDist(rng);
        std::vector<int> opTypes(numOps), opKeys(numOps), opVals(numOps);
        for (int i = 0; i < numOps; i++) {
            opTypes[i] = opDist(rng);
            opKeys[i] = keyDist(rng);
            opVals[i] = valDist(rng);
        }

        // Compute reference results using std::unordered_map
        std::unordered_map<int, int> ref;
        std::vector<int> refGet(numOps, 0);
        std::vector<bool> refBool(numOps, false);
        std::vector<int> refSize(numOps, 0);
        for (int i = 0; i < numOps; i++) {
            switch (opTypes[i]) {
                case 0:
                    ref[opKeys[i]] = opVals[i];
                    break;
                case 1: {
                    auto it = ref.find(opKeys[i]);
                    refGet[i] = (it != ref.end()) ? it->second : -1;
                    break;
                }
                case 2: {
                    refBool[i] = ref.count(opKeys[i]) > 0;
                    ref.erase(opKeys[i]);
                    break;
                }
                case 3:
                    refBool[i] = ref.count(opKeys[i]) > 0;
                    break;
                case 4:
                    refSize[i] = static_cast<int>(ref.size());
                    break;
            }
        }

        std::string desc = std::to_string(numOps) + " random ops";
        return harness::Case<bool>{
            desc,
            [opTypes, opKeys, opVals, refGet, refBool, refSize, numOps]() -> bool {
                MyHashMap m;
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
        };
    });

    return h;
}

} // namespace q1_tests
