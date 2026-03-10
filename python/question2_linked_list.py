"""
===============================================================
 PROBLEM 2 -- Custom Linked List
===============================================================

  Implement a singly linked list from scratch. Your linked list must
  support the following operations:

    add(value)        -- Append a value to the end of the list
    get(index)        -- Return the value at the given index (0-based)
    remove(index)     -- Remove and return the value at the given index
    contains(value)   -- Return true if the value exists in the list
    size()            -- Return the number of elements in the list
    reverse()         -- Reverse the list in-place

  You are given a Node class and the skeleton of a CustomLinkedList
  class. Fill in each method. Think carefully about:
    - Maintaining a 'head' reference and a 'size' counter
    - Edge cases: empty list, single element, first/last element
    - For reverse(): you can do this iteratively with three pointers

  -- Why Learn This? -----------------------------------------
  While linked lists are fundamental to CS education, they are
  rarely the best choice in practice. Arrays (and dynamic arrays
  like Python's list) have much better cache locality -- accessing
  sequential elements is fast because they sit next to each other
  in memory. Linked lists scatter nodes across the heap, causing
  frequent cache misses. However, understanding linked lists
  teaches you about references, dynamic memory, and the tradeoffs
  behind data structure choice -- which is exactly why we study
  them.

  Constraints:
    Values are integers in [-1000000, 1000000]
    Up to 100000 operations will be performed

  Run:
    python question2_linked_list.py

  Tip: Use .run_quick() instead of .run() to skip benchmarks during
       development.
===============================================================
"""

import sys
from question2_tests import build_harness


class Node:
    """Provided -- do not modify."""

    def __init__(self, value):
        self.value = value
        self.next = None


class CustomLinkedList:

    def __init__(self):
        # Hint: Initialize head (None) and a size counter.
        # TODO: Initialize your fields
        pass

    def add(self, value):
        """Append a value to the end of the list.
        Hint: If head is None, create a new Node as head.
              Otherwise, walk to the last node and set its .next."""
        # TODO: Implement
        pass

    def get(self, index):
        """Return the value at the given 0-based index.
        Hint: Walk forward from head 'index' times.
        Raises IndexError if index is invalid."""
        # TODO: Implement
        return -1

    def remove(self, index):
        """Remove and return the value at the given index.
        Hint: You need the previous node to skip over the removed one.
              Special-case index 0 (removing head).
        Raises IndexError if index is invalid."""
        # TODO: Implement
        return -1

    def contains(self, value):
        """Return True if the value exists in the list.
        Hint: Walk from head, checking each node's value."""
        # TODO: Implement
        return False

    def size(self):
        """Return the number of elements in the list."""
        # TODO: Implement
        return 0

    def reverse(self):
        """Reverse the list in-place.
        Hint: Use three variables -- prev, current, and next_node.
              Walk through, flipping each .next pointer backward."""
        # TODO: Implement
        pass


if __name__ == "__main__":
    passed = build_harness(CustomLinkedList) \
        .run()   # Tip: change to .run_quick() for faster feedback (skips benchmarks & scaling)
    # Add your own tests by chaining before .run():
    #   build_harness(CustomLinkedList) \
    #       .add_test("My test", lambda: (lambda ll: (ll.add(10), ll.get(0) == 10)[-1])(CustomLinkedList()), True) \
    #       .run()
    if not passed:
        sys.exit(1)
