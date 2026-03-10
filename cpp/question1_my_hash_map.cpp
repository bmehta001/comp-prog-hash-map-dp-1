/**
 * ===============================================================
 *  PROBLEM 1 -- Custom HashMap with Open Addressing
 * ===============================================================
 *
 *  Implement a hash map (dictionary) from scratch using open
 *  addressing with linear probing. Do NOT use std::unordered_map,
 *  std::map, or any similar container.
 *
 *  -- Concepts -----------------------------------------------
 *  * Open addressing: all entries live in the backing array (no
 *    linked lists). When a collision occurs, probe forward to
 *    find an open slot.
 *  * Linear probing: try index+1, index+2, ... wrapping around
 *    at the end.
 *  * Tombstones: when removing a key, mark the slot as "deleted"
 *    rather than clearing it, so probe chains aren't broken.
 *  * Resizing: as the table fills up, performance degrades. When
 *    the load factor (size / capacity) exceeds a threshold, grow
 *    the array and rehash all entries.
 *
 *  -- Why Linear Probing? ------------------------------------
 *  Another common approach is "separate chaining," where each
 *  array slot holds a linked list of entries that hashed to
 *  that index. We use linear probing instead because it keeps
 *  all data in a single contiguous array, which is much more
 *  cache-friendly. Modern CPUs access sequential memory
 *  locations far faster than following scattered pointers to
 *  heap-allocated list nodes. The tradeoff is that clusters
 *  of occupied slots can form, but with a good hash function
 *  and timely resizing, linear probing often outperforms
 *  chaining in practice.
 *
 *  -- Hash Function (provided -- do not modify) --------------
 *  The hash() method uses bit mixing to produce a non-negative
 *  integer from any int key. The return value can be very large
 *  (up to INT_MAX). It is YOUR job to figure out how to turn
 *  this into a valid array index.
 *
 *  -- Data Structures ----------------------------------------
 *  Starting capacity = 16, load-factor threshold = 0.7.
 *  Internal arrays (std::vector, grow dynamically):
 *    int  keys[]     -- stores the key at each slot
 *    int  values[]   -- stores the value at each slot
 *    bool occupied[] -- true if the slot has ever been written
 *    bool deleted[]  -- true if the slot is a tombstone
 *
 *  -- Methods to Implement -----------------------------------
 *    void put(int key, int value) -- insert or update; resize if needed
 *    int  get(int key)            -- return value or -1
 *    bool remove(int key)         -- tombstone; true if found
 *    bool containsKey(int key)    -- check existence
 *    int  size()                  -- active entries count
 *    void resize()                -- double capacity and rehash
 *
 *  -- Need Help? ---------------------------------------------
 *  See HINTS.md for pseudocode and step-by-step guidance.
 *
 *  Compile & run:
 *    g++ -std=c++17 -O2 question1_my_hash_map.cpp -o q1 && ./q1
 *    cl /std:c++17 /EHsc /O2 question1_my_hash_map.cpp /Fe:q1.exe && q1.exe
 * ===============================================================
 */

#include "test_harness.h"
#include <vector>

class MyHashMap {
public:
    static const int INITIAL_CAPACITY = 16;
    static constexpr double MAX_LOAD_FACTOR = 0.7;

private:
    std::vector<int> _keys;
    std::vector<int> _values;
    std::vector<bool> _occupied;
    std::vector<bool> _deleted;
    int _size;
    int _capacity;

    /**
     * Hash function -- DO NOT MODIFY.
     * Returns a non-negative integer derived from the key.
     * The result can be any value in [0, INT_MAX].
     */
    int hash(int key) const {
        unsigned int h = static_cast<unsigned int>(key);
        h ^= (h >> 16);
        h *= 0x85ebca6bu;
        h ^= (h >> 13);
        h *= 0xc2b2ae35u;
        h ^= (h >> 16);
        return static_cast<int>(h & 0x7FFFFFFFu);
    }

public:
    MyHashMap()
        : _keys(INITIAL_CAPACITY)
        , _values(INITIAL_CAPACITY)
        , _occupied(INITIAL_CAPACITY, false)
        , _deleted(INITIAL_CAPACITY, false)
        , _size(0)
        , _capacity(INITIAL_CAPACITY) {}

    /**
     * Insert or update a key-value pair.
     * If the key already exists, update its value.
     * If the load factor exceeds MAX_LOAD_FACTOR after inserting,
     * call resize().
     */
    void put(int key, int value) {
        // TODO: Implement put with linear probing
    }

    /**
     * Return the value associated with key, or -1 if not found.
     */
    int get(int key) const {
        // TODO: Implement get with linear probing
        return -1;
    }

    /**
     * Remove the key by marking its slot as a tombstone.
     * Return true if found and removed, false otherwise.
     */
    bool remove(int key) {
        // TODO: Implement remove with linear probing
        return false;
    }

    /**
     * Return true if the key exists in the map (and is not deleted).
     */
    bool containsKey(int key) const {
        // TODO: Implement containsKey
        return false;
    }

    /**
     * Return the number of active (non-deleted) entries.
     */
    int size() const {
        // TODO: Return _size
        return 0;
    }

private:
    /**
     * Double the capacity, allocate new arrays, and re-insert every
     * active entry. Tombstones should be discarded during rehashing.
     */
    void resize() {
        // TODO: Implement resize (double capacity, rehash all active entries)
    }
};

// Include tests after MyHashMap is fully defined
#include "question1_tests.h"

int main() {
    auto h = q1_tests::newHarness();
    bool passed = q1_tests::addTests(h)
        // Add your own tests here:
        // .addTest("My test", [](){ MyHashMap m; m.put(1, 10); return m.get(1) == 10; }, true)
        .run();   // Tip: change to .runQuick() for faster feedback (skips benchmarks & scaling)
    return passed ? 0 : 1;
}
