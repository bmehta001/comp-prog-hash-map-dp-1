/**
 * ═══════════════════════════════════════════════════════════
 *  PROBLEM 2 — Custom Linked List
 * ═══════════════════════════════════════════════════════════
 *
 *  Implement a singly linked list from scratch. Your linked list must
 *  support the following operations:
 *
 *    add(value)        -- Append a value to the end of the list
 *    get(index)        -- Return the value at the given index (0-based)
 *    remove(index)     -- Remove and return the value at the given index
 *    contains(value)   -- Return true if the value exists in the list
 *    size()            -- Return the number of elements in the list
 *    reverse()         -- Reverse the list in-place
 *
 *  You are given a Node inner class and the skeleton of a CustomLinkedList
 *  class. Fill in each method. Think carefully about:
 *    - Maintaining a 'head' reference and a 'size' counter
 *    - Edge cases: empty list, single element, first/last element
 *    - For reverse(): you can do this iteratively with three pointers
 *
 *  ── Why Learn This? ─────────────────────────────────────────
 *  While linked lists are fundamental to CS education, they are rarely
 *  the best choice in practice. Arrays (and dynamic arrays like
 *  ArrayList) have much better cache locality — accessing sequential
 *  elements is fast because they sit next to each other in memory.
 *  Linked lists scatter nodes across the heap, causing frequent cache
 *  misses. However, understanding linked lists teaches you about
 *  references, dynamic memory, and the tradeoffs behind data
 *  structure choice — which is exactly why we study them.
 *
 *  Constraints:
 *    Values are integers in [-1000000, 1000000]
 *    Up to 100000 operations will be performed
 *
 *  Compile & run:
 *    javac *.java
 *    java Question2_LinkedList
 *
 *  Tip: Use .runQuick() instead of .run() to skip benchmarks during
 *       development.
 * ═══════════════════════════════════════════════════════════
 */

public class Question2_LinkedList {

    // --- Inner Node class (provided -- do not modify) ---
    static class Node {
        int value;
        Node next;

        Node(int value) {
            this.value = value;
            this.next = null;
        }
    }

    // --- Your linked list implementation ---
    static class CustomLinkedList {
        // Hint: You'll want a 'head' node reference and a size counter.
        //       head starts as null (empty list).

        // TODO: Declare your fields here


        public CustomLinkedList() {
            // TODO: Initialize your fields
        }

        /**
         * Append a value to the END of the list.
         * Hint: If the list is empty, the new node becomes head.
         *       Otherwise, walk to the last node and set its .next.
         */
        public void add(int value) {
            // TODO: Implement
        }

        /**
         * Return the value at the given 0-based index.
         * Hint: Start at head and walk forward 'index' times.
         * @throws IndexOutOfBoundsException if index is invalid
         */
        public int get(int index) {
            // TODO: Implement
            return -1;
        }

        /**
         * Remove and return the value at the given 0-based index.
         * Hint: To remove a node, you need the PREVIOUS node's .next
         *       to skip over the removed node. Special-case index 0.
         * @throws IndexOutOfBoundsException if index is invalid
         */
        public int remove(int index) {
            // TODO: Implement
            return -1;
        }

        /**
         * Return true if the value exists anywhere in the list.
         * Hint: Walk from head, checking each node's value.
         */
        public boolean contains(int value) {
            // TODO: Implement
            return false;
        }

        /**
         * Return the number of elements currently in the list.
         */
        public int size() {
            // TODO: Implement
            return 0;
        }

        /**
         * Reverse the list in-place.
         * Hint: Use three references -- previous, current, and next.
         *       Walk through the list, flipping each node's .next pointer
         *       to point backward instead of forward.
         */
        public void reverse() {
            // TODO: Implement
        }
    }

    public static void main(String[] args) {
        boolean passed = Question2_Tests.buildHarness()
            // Add your own tests here:
            // .addTest("My test", () -> {
            //     CustomLinkedList ll = new CustomLinkedList();
            //     ll.add(10);
            //     return ll.get(0) == 10;
            // }, true)
            .run();   // Tip: change to .runQuick() for faster feedback (skips benchmarks & scaling)
        if (!passed) {
            System.exit(1);
        }
    }
}
