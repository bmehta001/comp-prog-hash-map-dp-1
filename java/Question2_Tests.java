import java.util.*;
import java.util.function.*;

public class Question2_Tests {

    public static TestHarness<Boolean> buildHarness() {
        Random rng = new Random(42);

        return TestHarness.<Boolean>forProblem("Custom Linked List")

            // ── Correctness tests ───────────────────────────

            .addTest("add_and_size", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                for (int i = 0; i < 5; i++) {
                    ll.add(i * 10);
                }
                return ll.size() == 5;
            }, true)

            .addTest("get_elements", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                ll.add(10);
                ll.add(20);
                ll.add(30);
                return ll.get(0) == 10 && ll.get(1) == 20 && ll.get(2) == 30;
            }, true)

            .addTest("remove_first", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                ll.add(1);
                ll.add(2);
                ll.add(3);
                int removed = ll.remove(0);
                return removed == 1 && ll.size() == 2 && ll.get(0) == 2;
            }, true)

            .addTest("remove_last", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                ll.add(1);
                ll.add(2);
                ll.add(3);
                int removed = ll.remove(2);
                return removed == 3 && ll.size() == 2;
            }, true)

            .addTest("remove_middle", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                ll.add(1);
                ll.add(2);
                ll.add(3);
                int removed = ll.remove(1);
                return removed == 2 && ll.get(0) == 1 && ll.get(1) == 3;
            }, true)

            .addTest("contains_true", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                ll.add(5);
                ll.add(10);
                ll.add(15);
                return ll.contains(10);
            }, true)

            .addTest("contains_false", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                ll.add(5);
                ll.add(10);
                ll.add(15);
                return !ll.contains(20);
            }, true)

            .addTest("reverse_list", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                for (int i = 1; i <= 5; i++) {
                    ll.add(i);
                }
                ll.reverse();
                return ll.get(0) == 5
                    && ll.get(1) == 4
                    && ll.get(2) == 3
                    && ll.get(3) == 2
                    && ll.get(4) == 1;
            }, true)

            .addTest("reverse_single", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                ll.add(42);
                ll.reverse();
                return ll.get(0) == 42 && ll.size() == 1;
            }, true)

            .addTest("reverse_empty", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                ll.reverse();
                return ll.size() == 0;
            }, true)

            .addTest("empty_size", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                return ll.size() == 0;
            }, true)

            .addTest("get_out_of_bounds", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                ll.add(1);
                try {
                    ll.get(-1);
                    return false;
                } catch (IndexOutOfBoundsException e) {
                    // expected
                }
                try {
                    ll.get(1);
                    return false;
                } catch (IndexOutOfBoundsException e) {
                    // expected
                }
                // Also test on empty list
                Question2_LinkedList.CustomLinkedList empty = new Question2_LinkedList.CustomLinkedList();
                try {
                    empty.get(0);
                    return false;
                } catch (IndexOutOfBoundsException e) {
                    // expected
                }
                return true;
            }, true)

            .addTest("remove_out_of_bounds", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                ll.add(1);
                ll.add(2);
                ll.add(3);
                try {
                    ll.remove(5);
                    return false;
                } catch (IndexOutOfBoundsException e) {
                    // expected
                }
                try {
                    ll.remove(-1);
                    return false;
                } catch (IndexOutOfBoundsException e) {
                    // expected
                }
                return true;
            }, true)

            // ── Benchmark ───────────────────────────────────

            .addBenchmark("10,000 add + 1,000 random get", () -> {
                Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                for (int i = 0; i < 10_000; i++) {
                    ll.add(i);
                }
                Random bench = new Random(42);
                int sum = 0;
                for (int i = 0; i < 1_000; i++) {
                    sum += ll.get(bench.nextInt(ll.size()));
                }
                return sum != Integer.MIN_VALUE;
            })

            // ── Scaling analysis ────────────────────────────

            .addScaling("N (add operations)",
                new int[]{100, 500, 1_000, 5_000, 10_000},
                n -> n,
                (Integer n) -> {
                    Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                    for (int i = 0; i < n; i++) {
                        ll.add(i);
                    }
                    return ll.size() > 0;
                })

            // ── Random stress tests ─────────────────────────

            .addRandomTests("vs java.util.LinkedList", 1000, () -> {
                int numOps = 20 + rng.nextInt(31);
                int[] opTypes = new int[numOps];
                int[] opArgs = new int[numOps];
                for (int i = 0; i < numOps; i++) {
                    opTypes[i] = rng.nextInt(5);
                    opArgs[i] = rng.nextInt(200) - 50;
                }

                // Compute reference results using java.util.LinkedList
                LinkedList<Integer> ref = new LinkedList<>();
                List<String> refResults = new ArrayList<>();
                for (int i = 0; i < numOps; i++) {
                    switch (opTypes[i]) {
                        case 0: {
                            // add
                            ref.add(opArgs[i]);
                            refResults.add("add");
                            break;
                        }
                        case 1: {
                            // get (only if non-empty)
                            if (ref.isEmpty()) {
                                refResults.add("skip");
                            } else {
                                int idx = Math.abs(opArgs[i]) % ref.size();
                                refResults.add("get:" + ref.get(idx));
                                opArgs[i] = idx;
                            }
                            break;
                        }
                        case 2: {
                            // remove (only if non-empty)
                            if (ref.isEmpty()) {
                                refResults.add("skip");
                            } else {
                                int idx = Math.abs(opArgs[i]) % ref.size();
                                int val = ref.remove(idx);
                                refResults.add("remove:" + val);
                                opArgs[i] = idx;
                            }
                            break;
                        }
                        case 3: {
                            // contains
                            boolean found = ref.contains(opArgs[i]);
                            refResults.add("contains:" + found);
                            break;
                        }
                        case 4: {
                            // size
                            refResults.add("size:" + ref.size());
                            break;
                        }
                    }
                }

                int[] opTypesCopy = Arrays.copyOf(opTypes, numOps);
                int[] opArgsCopy = Arrays.copyOf(opArgs, numOps);
                List<String> refCopy = new ArrayList<>(refResults);

                return new TestHarness.Case<>(
                    numOps + " random ops",
                    () -> {
                        Question2_LinkedList.CustomLinkedList ll = new Question2_LinkedList.CustomLinkedList();
                        for (int i = 0; i < numOps; i++) {
                            String expected = refCopy.get(i);
                            if (expected.equals("skip")) {
                                continue;
                            }
                            switch (opTypesCopy[i]) {
                                case 0: {
                                    ll.add(opArgsCopy[i]);
                                    break;
                                }
                                case 1: {
                                    int got = ll.get(opArgsCopy[i]);
                                    int exp = Integer.parseInt(expected.split(":")[1]);
                                    if (got != exp) {
                                        return false;
                                    }
                                    break;
                                }
                                case 2: {
                                    int got = ll.remove(opArgsCopy[i]);
                                    int exp = Integer.parseInt(expected.split(":")[1]);
                                    if (got != exp) {
                                        return false;
                                    }
                                    break;
                                }
                                case 3: {
                                    boolean got = ll.contains(opArgsCopy[i]);
                                    boolean exp = Boolean.parseBoolean(expected.split(":")[1]);
                                    if (got != exp) {
                                        return false;
                                    }
                                    break;
                                }
                                case 4: {
                                    int got = ll.size();
                                    int exp = Integer.parseInt(expected.split(":")[1]);
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
                );
            });
    }
}
