/**
 * ===========================================================
 *  PROBLEM 1 -- Custom HashMap with Open Addressing
 * ===========================================================
 *
 *  Implement a hash map (dictionary) from scratch using open addressing
 *  with linear probing. Do NOT use Java's built-in HashMap, HashSet, or
 *  any similar collection.
 *
 *  -- Concepts ---------------------------------------------
 *  * Open addressing: all entries live in the backing array (no linked
 *    lists). When a collision occurs, probe forward to find an open slot.
 *  * Linear probing: try index+1, index+2, ... wrapping around at the end.
 *  * Tombstones: when removing a key, mark the slot as "deleted" rather
 *    than clearing it, so that probe chains aren't broken.
 *  * Resizing: as the table fills up, performance degrades. When the
 *    load factor (size / capacity) exceeds a threshold, grow the array
 *    and rehash all entries.
 *
 *  -- Why Linear Probing? -------------------------------------
 *  Another common approach is "separate chaining," where each array
 *  slot holds a linked list of entries that hashed to that index.
 *  We use linear probing instead because it keeps all data in a
 *  single contiguous array, which is much more cache-friendly.
 *  Modern CPUs access sequential memory locations far faster than
 *  following scattered pointers to heap-allocated list nodes. The
 *  tradeoff is that clusters of occupied slots can form, but with
 *  a good hash function and timely resizing, linear probing often
 *  outperforms chaining in practice.
 *
 *  -- Hash Function (provided -- do not modify) -------------
 *  The hash() method uses bit mixing to produce a non-negative integer
 *  from any int key. The return value can be anywhere in [0, 2^31 - 1].
 *  It is YOUR job to figure out how to turn this into a valid array index.
 *  Keys can be any integer (positive, negative, or zero).
 *
 *  -- Data Structures--------------------------------------
 *  Starting capacity = 16, load-factor threshold = 0.7.
 *  Internal arrays (grow dynamically when resizing):
 *    int[]     keys     -- stores the key at each slot
 *    int[]     values   -- stores the value at each slot
 *    boolean[] occupied -- true if the slot has ever been written to
 *    boolean[] deleted  -- true if the slot is a tombstone
 *
 *  -- Methods to Implement ---------------------------------
 *    void    put(int key, int value)  -- insert or update; resize if needed
 *    int     get(int key)             -- return value or -1 if missing
 *    boolean remove(int key)          -- mark tombstone; true if found
 *    boolean containsKey(int key)     -- check existence
 *    int     size()                   -- active (non-deleted) entries
 *    void    resize()                 -- double capacity and rehash
 *
 *  -- Need Help? -------------------------------------------
 *  See HINTS.md for pseudocode and step-by-step guidance.
 *
 *  Compile & run:
 *    javac *.java
 *    java Question1_MyHashMap
 * ===========================================================
 */

class MyHashMap {
    private static final int INITIAL_CAPACITY = 16;
    private static final double MAX_LOAD_FACTOR = 0.7;

    private int[] keys;
    private int[] values;
    private boolean[] occupied;
    private boolean[] deleted;
    private int size;
    private int capacity;

    /**
     * Hash function -- DO NOT MODIFY.
     * Returns a non-negative integer derived from the key.
     * The result can be any value in [0, 2^31 - 1].
     */
    private int hash(int key) {
        int h = key;
        h ^= (h >>> 16);
        h *= 0x85ebca6b;
        h ^= (h >>> 13);
        h *= 0xc2b2ae35;
        h ^= (h >>> 16);
        return h & 0x7FFFFFFF;
    }

    public MyHashMap() {
        this.capacity = INITIAL_CAPACITY;
        this.keys = new int[capacity];
        this.values = new int[capacity];
        this.occupied = new boolean[capacity];
        this.deleted = new boolean[capacity];
        this.size = 0;
    }

    /**
     * Insert or update a key-value pair.
     * If the key already exists, update its value.
     * If the load factor exceeds MAX_LOAD_FACTOR after inserting, call resize().
     */
    public void put(int key, int value) {
        // TODO: Implement put with linear probing
    }

    /**
     * Return the value associated with key, or -1 if not found.
     */
    public int get(int key) {
        // TODO: Implement get with linear probing
        return -1;
    }

    /**
     * Remove the key from the map by marking its slot as a tombstone.
     * Return true if the key was found and removed, false otherwise.
     */
    public boolean remove(int key) {
        // TODO: Implement remove with linear probing
        return false;
    }

    /**
     * Return true if the key exists in the map (and is not deleted).
     */
    public boolean containsKey(int key) {
        // TODO: Implement containsKey
        return false;
    }

    /**
     * Return the number of active (non-deleted) entries.
     */
    public int size() {
        // TODO: Return the current size
        return 0;
    }

    /**
     * Double the capacity, allocate new arrays, and re-insert every
     * active entry. Tombstones should be discarded during rehashing.
     */
    private void resize() {
        // TODO: Implement resize (double capacity, rehash all active entries)
    }
}

public class Question1_MyHashMap {

    public static void main(String[] args) {
        boolean passed = Question1_Tests.buildHarness()
            // Add your own tests here:
            // .addTest("My test", () -> {
            //     MyHashMap m = new MyHashMap();
            //     m.put(1, 10);
            //     return m.get(1) == 10;
            // }, true)
            .run();   // Tip: change to .runQuick() for faster feedback (skips benchmarks & scaling)
        if (!passed) {
            System.exit(1);
        }
    }
}
