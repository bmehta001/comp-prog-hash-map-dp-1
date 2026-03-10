/**
 * Test infrastructure for Question 5 -- Custom Linked List.
 *
 * NOTE: This header must be included AFTER both "test_harness.h" and the
 * CustomLinkedList class definition. It references CustomLinkedList directly.
 */
#pragma once

#include <random>
#include <list>
#include <vector>
#include <string>
#include <cmath>

namespace q2_tests {

inline harness::TestHarness<bool> newHarness() {
    return harness::TestHarness<bool>::forProblem("Custom Linked List");
}

inline harness::TestHarness<bool>& addTests(harness::TestHarness<bool>& h) {

    // ── Correctness tests ───────────────────────────────

    h.addTest("add_and_size", []() {
        CustomLinkedList ll;
        for (int i = 0; i < 5; i++) {
            ll.add(i * 10);
        }
        return ll.size() == 5;
    }, true);

    h.addTest("get_elements", []() {
        CustomLinkedList ll;
        ll.add(10);
        ll.add(20);
        ll.add(30);
        return ll.get(0) == 10 && ll.get(1) == 20 && ll.get(2) == 30;
    }, true);

    h.addTest("remove_first", []() {
        CustomLinkedList ll;
        ll.add(1);
        ll.add(2);
        ll.add(3);
        int removed = ll.remove(0);
        return removed == 1 && ll.size() == 2 && ll.get(0) == 2;
    }, true);

    h.addTest("remove_last", []() {
        CustomLinkedList ll;
        ll.add(1);
        ll.add(2);
        ll.add(3);
        int removed = ll.remove(2);
        return removed == 3 && ll.size() == 2;
    }, true);

    h.addTest("remove_middle", []() {
        CustomLinkedList ll;
        ll.add(1);
        ll.add(2);
        ll.add(3);
        int removed = ll.remove(1);
        return removed == 2 && ll.get(0) == 1 && ll.get(1) == 3;
    }, true);

    h.addTest("contains_true", []() {
        CustomLinkedList ll;
        ll.add(5);
        ll.add(10);
        ll.add(15);
        return ll.contains(10);
    }, true);

    h.addTest("contains_false", []() {
        CustomLinkedList ll;
        ll.add(5);
        ll.add(10);
        ll.add(15);
        return !ll.contains(20);
    }, true);

    h.addTest("reverse_list", []() {
        CustomLinkedList ll;
        for (int i = 1; i <= 5; i++) {
            ll.add(i);
        }
        ll.reverse();
        return ll.get(0) == 5
            && ll.get(1) == 4
            && ll.get(2) == 3
            && ll.get(3) == 2
            && ll.get(4) == 1;
    }, true);

    h.addTest("reverse_single", []() {
        CustomLinkedList ll;
        ll.add(42);
        ll.reverse();
        return ll.get(0) == 42 && ll.size() == 1;
    }, true);

    h.addTest("reverse_empty", []() {
        CustomLinkedList ll;
        ll.reverse();
        return ll.size() == 0;
    }, true);

    h.addTest("empty_size", []() {
        CustomLinkedList ll;
        return ll.size() == 0;
    }, true);

    h.addTest("get_out_of_bounds", []() {
        CustomLinkedList ll;
        ll.add(1);
        try {
            ll.get(-1);
            return false;
        } catch (const std::out_of_range&) {
            // expected
        }
        try {
            ll.get(1);
            return false;
        } catch (const std::out_of_range&) {
            // expected
        }
        // Also test on empty list
        CustomLinkedList empty;
        try {
            empty.get(0);
            return false;
        } catch (const std::out_of_range&) {
            // expected
        }
        return true;
    }, true);

    h.addTest("remove_out_of_bounds", []() {
        CustomLinkedList ll;
        ll.add(1);
        ll.add(2);
        ll.add(3);
        try {
            ll.remove(5);
            return false;
        } catch (const std::out_of_range&) {
            // expected
        }
        try {
            ll.remove(-1);
            return false;
        } catch (const std::out_of_range&) {
            // expected
        }
        return true;
    }, true);

    // ── Benchmark ───────────────────────────────────────

    h.addBenchmark("10,000 add + 1,000 random get", []() {
        CustomLinkedList ll;
        for (int i = 0; i < 10000; i++) {
            ll.add(i);
        }
        std::mt19937 bench(42);
        std::uniform_int_distribution<int> dist(0, 9999);
        int sum = 0;
        for (int i = 0; i < 1000; i++) {
            sum += ll.get(dist(bench));
        }
        return sum != std::numeric_limits<int>::min();
    });

    // ── Scaling analysis ────────────────────────────────

    h.addScaling<int>(
        "N (add operations)",
        {100, 500, 1000, 5000, 10000},
        std::function<int(int)>([](int n) -> int {
            return n;
        }),
        std::function<bool(const int&)>([](const int& n) -> bool {
            CustomLinkedList ll;
            for (int i = 0; i < n; i++) {
                ll.add(i);
            }
            return ll.size() > 0;
        })
    );

    // ── Random stress tests ─────────────────────────────

    static std::mt19937 rng(42);

    h.addRandomTests("vs std::list", 1000, []() -> harness::Case<bool> {
        std::uniform_int_distribution<int> numOpsDist(20, 50);
        std::uniform_int_distribution<int> opDist(0, 4);
        std::uniform_int_distribution<int> argDist(-50, 149);

        int numOps = numOpsDist(rng);
        std::vector<int> opTypes(numOps), opArgs(numOps);
        for (int i = 0; i < numOps; i++) {
            opTypes[i] = opDist(rng);
            opArgs[i] = argDist(rng);
        }

        // Compute reference results using std::list
        std::list<int> ref;
        std::vector<std::string> refResults(numOps);
        for (int i = 0; i < numOps; i++) {
            switch (opTypes[i]) {
                case 0: {
                    // add
                    ref.push_back(opArgs[i]);
                    refResults[i] = "add";
                    break;
                }
                case 1: {
                    // get (only if non-empty)
                    if (ref.empty()) {
                        refResults[i] = "skip";
                    } else {
                        int idx = std::abs(opArgs[i]) % static_cast<int>(ref.size());
                        auto it = ref.begin();
                        std::advance(it, idx);
                        refResults[i] = "get:" + std::to_string(*it);
                        opArgs[i] = idx;
                    }
                    break;
                }
                case 2: {
                    // remove (only if non-empty)
                    if (ref.empty()) {
                        refResults[i] = "skip";
                    } else {
                        int idx = std::abs(opArgs[i]) % static_cast<int>(ref.size());
                        auto it = ref.begin();
                        std::advance(it, idx);
                        int val = *it;
                        ref.erase(it);
                        refResults[i] = "remove:" + std::to_string(val);
                        opArgs[i] = idx;
                    }
                    break;
                }
                case 3: {
                    // contains
                    bool found = false;
                    for (int v : ref) {
                        if (v == opArgs[i]) {
                            found = true;
                            break;
                        }
                    }
                    refResults[i] = std::string("contains:") + (found ? "1" : "0");
                    break;
                }
                case 4: {
                    // size
                    refResults[i] = "size:" + std::to_string(ref.size());
                    break;
                }
            }
        }

        std::string desc = std::to_string(numOps) + " random ops";
        return harness::Case<bool>{
            desc,
            [opTypes, opArgs, refResults, numOps]() -> bool {
                CustomLinkedList ll;
                for (int i = 0; i < numOps; i++) {
                    if (refResults[i] == "skip") {
                        continue;
                    }
                    switch (opTypes[i]) {
                        case 0: {
                            ll.add(opArgs[i]);
                            break;
                        }
                        case 1: {
                            int got = ll.get(opArgs[i]);
                            int exp = std::stoi(refResults[i].substr(4));
                            if (got != exp) {
                                return false;
                            }
                            break;
                        }
                        case 2: {
                            int got = ll.remove(opArgs[i]);
                            int exp = std::stoi(refResults[i].substr(7));
                            if (got != exp) {
                                return false;
                            }
                            break;
                        }
                        case 3: {
                            bool got = ll.contains(opArgs[i]);
                            bool exp = refResults[i].substr(9) == "1";
                            if (got != exp) {
                                return false;
                            }
                            break;
                        }
                        case 4: {
                            int got = ll.size();
                            int exp = std::stoi(refResults[i].substr(5));
                            if (got != exp) {
                                return false;
                            }
                            break;
                        }
                    }
                }
                return true;
            },
            true
        };
    });

    return h;
}

} // namespace q2_tests
