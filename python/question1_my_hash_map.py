"""
===============================================================
 PROBLEM 1 -- Custom HashMap with Open Addressing
===============================================================

  Implement a hash map (dictionary) from scratch using open
  addressing with linear probing. Do NOT use Python's built-in
  dict, set, or any similar collection.

  -- Concepts ------------------------------------------------
  * Open addressing: all entries live in the backing array (no
    linked lists). When a collision occurs, probe forward to
    find an open slot.
  * Linear probing: try index+1, index+2, ... wrapping around
    at the end.
  * Tombstones: when removing a key, mark the slot as "deleted"
    rather than clearing it, so probe chains aren't broken.
  * Resizing: as the table fills up, performance degrades. When
    the load factor (size / capacity) exceeds a threshold, grow
    the array and rehash all entries.

  -- Why Linear Probing? ------------------------------------
  Another common approach is "separate chaining," where each
  array slot holds a linked list of entries that hashed to
  that index. We use linear probing instead because it keeps
  all data in a single contiguous array, which is much more
  cache-friendly. Modern CPUs access sequential memory
  locations far faster than following scattered pointers to
  heap-allocated list nodes. The tradeoff is that clusters
  of occupied slots can form, but with a good hash function
  and timely resizing, linear probing often outperforms
  chaining in practice.

  -- Hash Function (provided -- do not modify) ---------------
  The _hash() method uses bit mixing to produce a non-negative
  integer from any key. The return value can be anywhere in
  [0, 2^31 - 1]. It is YOUR job to figure out how to turn
  this into a valid array index.
  Keys can be any integer (positive, negative, or zero).

  -- Data Structures -----------------------------------------
  Starting capacity = 16, load-factor threshold = 0.7.
  Internal arrays (grow dynamically when resizing):
    keys     -- stores the key at each slot
    values   -- stores the value at each slot
    occupied -- True if the slot has ever been written to
    deleted  -- True if the slot is a tombstone

  -- Methods to Implement ------------------------------------
    put(key, value)   -- insert or update; resize if needed
    get(key)          -- return value or -1 if missing
    remove(key)       -- mark tombstone; return True if found
    contains_key(key) -- check existence
    size()            -- active (non-deleted) entries
    _resize()         -- double capacity and rehash

  -- Need Help? ----------------------------------------------
  See HINTS.md for pseudocode and step-by-step guidance.

  Run:
    python question1_my_hash_map.py
===============================================================
"""

import sys
from question1_tests import build_harness


class MyHashMap:
    INITIAL_CAPACITY = 16
    MAX_LOAD_FACTOR = 0.7

    def __init__(self):
        self._capacity = self.INITIAL_CAPACITY
        self._keys = [0] * self._capacity
        self._values = [0] * self._capacity
        self._occupied = [False] * self._capacity
        self._deleted = [False] * self._capacity
        self._size = 0

    def _hash(self, key):
        """
        Hash function -- DO NOT MODIFY.
        Returns a non-negative integer derived from the key.
        The result can be any value in [0, 2^31 - 1].
        """
        h = key & 0xFFFFFFFF
        h ^= (h >> 16)
        h = (h * 0x85ebca6b) & 0xFFFFFFFF
        h ^= (h >> 13)
        h = (h * 0xc2b2ae35) & 0xFFFFFFFF
        h ^= (h >> 16)
        return h & 0x7FFFFFFF

    def put(self, key, value):
        """
        Insert or update a key-value pair.
        If the key already exists, update its value.
        If the load factor exceeds MAX_LOAD_FACTOR after inserting,
        call _resize().
        """
        # TODO: Implement put with linear probing
        pass

    def get(self, key):
        """
        Return the value associated with key, or -1 if not found.
        """
        # TODO: Implement get with linear probing
        return -1

    def remove(self, key):
        """
        Remove the key by marking its slot as a tombstone.
        Return True if found and removed, False otherwise.
        """
        # TODO: Implement remove with linear probing
        return False

    def contains_key(self, key):
        """Return True if the key exists in the map (and is not deleted)."""
        # TODO: Implement contains_key
        return False

    def size(self):
        """Return the number of active (non-deleted) entries."""
        # TODO: Return the current size
        return 0

    def _resize(self):
        """
        Double the capacity, allocate new arrays, and re-insert every
        active entry. Tombstones should be discarded during rehashing.
        """
        # TODO: Implement resize (double capacity, rehash all active entries)
        pass


if __name__ == "__main__":
    passed = build_harness(MyHashMap) \
        .run()   # Tip: change to .run_quick() for faster feedback (skips benchmarks & scaling)
    # Add your own tests by chaining before .run():
    #   build_harness(MyHashMap) \
    #       .add_test("My test", lambda: (lambda m: (m.put(1, 10), m.get(1) == 10)[-1])(MyHashMap()), True) \
    #       .run()
    if not passed:
        sys.exit(1)
