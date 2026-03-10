/**
 * ===============================================================
 *  PROBLEM 2 -- Custom Linked List
 * ===============================================================
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
 *  You are given a Node struct and the skeleton of a CustomLinkedList
 *  class. Fill in each method. Think carefully about:
 *    - Maintaining a 'head' pointer and a 'size' counter
 *    - Edge cases: empty list, single element, first/last element
 *    - For reverse(): you can do this iteratively with three pointers
 *    - Use 'new' to allocate nodes and 'delete' to free them
 *    - Implement a destructor to prevent memory leaks
 *    - Be careful with pointer manipulation!
 *
 *  -- Why Learn This? ----------------------------------------
 *  While linked lists are fundamental to CS education, they are
 *  rarely the best choice in practice. Arrays (and dynamic arrays
 *  like std::vector) have much better cache locality — accessing
 *  sequential elements is fast because they sit next to each other
 *  in memory. Linked lists scatter nodes across the heap, causing
 *  frequent cache misses. However, understanding linked lists
 *  teaches you about pointers, dynamic memory management, and the
 *  tradeoffs behind data structure choice — which is exactly why
 *  we study them.
 *
 *  Constraints:
 *    Values are integers in [-1000000, 1000000]
 *    Up to 100000 operations will be performed
 *
 *  Compile & run:
 *    g++ -std=c++17 -O2 -o question2 question2_linked_list.cpp
 *    cl /std:c++17 /EHsc /O2 question2_linked_list.cpp /Fe:q2.exe && q2.exe
 *
 *  Tip: Use .runQuick() instead of .run() to skip benchmarks during
 *       development.
 * ===============================================================
 */

#include "test_harness.h"
#include <stdexcept>

struct Node {
    int value;
    Node* next;

    Node(int val) : value(val), next(nullptr) {}
};

class CustomLinkedList {
public:
    // Hint: You'll want a Node* head and an int for size.
    //       head starts as nullptr (empty list).

    // TODO: Declare your fields here

    CustomLinkedList() {
        // TODO: Initialize your fields
    }

    /**
     * Destructor: Clean up ALL nodes to prevent memory leaks.
     * Hint: Walk from head, deleting each node. Use a temp pointer
     *       to hold the next node before deleting the current one.
     */
    ~CustomLinkedList() {
        // TODO: Implement -- use 'delete' on each node
    }

    /**
     * Append a value to the END of the list.
     * Hint: Create a new Node with 'new Node(value)'.
     *       If head is nullptr, it becomes the new head.
     *       Otherwise, walk to the last node and set its ->next.
     */
    void add(int value) {
        // TODO: Implement
    }

    /**
     * Return the value at the given 0-based index.
     * Hint: Start at head and walk forward 'index' times using ->next.
     * Throws std::out_of_range if index is invalid.
     */
    int get(int index) {
        // TODO: Implement
        return -1;
    }

    /**
     * Remove and return the value at the given 0-based index.
     * Hint: Find the node, unlink it by updating the previous node's ->next,
     *       save the value, then 'delete' the removed node to free memory.
     *       Special-case index 0 (removing head).
     * Throws std::out_of_range if index is invalid.
     */
    int remove(int index) {
        // TODO: Implement
        return -1;
    }

    /**
     * Return true if the value exists anywhere in the list.
     * Hint: Walk from head using ->next, checking each node's value.
     */
    bool contains(int value) {
        // TODO: Implement
        return false;
    }

    /**
     * Return the number of elements currently in the list.
     */
    int size() {
        // TODO: Implement
        return 0;
    }

    /**
     * Reverse the list in-place.
     * Hint: Use three pointers -- prev, current, and next.
     *       Walk through, flipping each ->next to point backward.
     *       After the loop, set head = prev.
     */
    void reverse() {
        // TODO: Implement
    }
};

// Include tests after CustomLinkedList is fully defined
#include "question2_tests.h"

int main() {
    auto h = q2_tests::newHarness();
    bool passed = q2_tests::addTests(h)
        // Add your own tests here:
        // .addTest("My test", [](){ CustomLinkedList ll; ll.add(10); return ll.get(0) == 10; }, true)
        .run();   // Tip: change to .runQuick() for faster feedback (skips benchmarks & scaling)
    return passed ? 0 : 1;
}
