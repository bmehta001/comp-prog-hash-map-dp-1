# Hints -- Question 1: Custom HashMap

These hints are meant to guide you if you get stuck. Try each method
on your own first before reading ahead.

---

## Hint 1: Array Indexing

The provided `hash()` function returns a **non-negative integer** that
can be anywhere in the range `[0, 2,147,483,647]`. You need to map
this to a valid array index in the range `[0, capacity)`.

What single mathematical operation constrains any non-negative integer
to a fixed range?

Think about the **modulo operator (`%`)**, which gives the remainder
after division. For example, `17 % 5 = 2`. So `hash(key) % capacity`
will always produce an index in the range `[0, capacity)`.

---

**Note:** The hints below use pseudocode -- you'll need to adapt the
logic to your chosen language's syntax.

## Hint 2: Linear Probing -- Finding a Key

```
index = startIndex
while occupied[index]:
    if not deleted[index] and keys[index] == key:
        return index        // found it
    index = (index + 1) % capacity
return NOT_FOUND            // hit an empty slot
```

---

## Hint 3: Linear Probing -- Inserting a Key

When inserting, you may encounter tombstones (deleted slots) along the
probe chain. You want to reuse the **first** tombstone for efficiency,
but you must **keep probing** to check whether the key already exists
further along.

```
firstTombstone = -1
index = startIndex
while occupied[index]:
    if deleted[index] and firstTombstone == -1:
        firstTombstone = index
    else if not deleted[index] and keys[index] == key:
        values[index] = value       // update existing key
        return
    index = (index + 1) % capacity
// Key not found -- insert at firstTombstone (if found), else at index
insertAt = (firstTombstone != -1) ? firstTombstone : index
keys[insertAt] = key
values[insertAt] = value
occupied[insertAt] = true
deleted[insertAt] = false
size++
```

---

## Hint 4: Why Tombstones?

Suppose you insert keys A, B, C and they probe to consecutive slots
5, 6, 7. If you delete B by **clearing** slot 6, then looking up C
would stop at the now-empty slot 6 and incorrectly report "not found."

A "tombstone" is a marker that says: "something used to be here, keep
searching." When you remove a key, don't clear the slot entirely --
instead, mark it as deleted. This tells the probing logic to keep
walking past the slot instead of stopping. Without tombstones,
removing any key could break the chain of probes, making other keys
unfindable.

---

## Hint 5: Resizing

As the table fills up, probe chains get longer and performance degrades.
The **load factor** is `size / capacity`. When it exceeds a threshold
(e.g., 0.7), you should:

1. Create new, larger arrays (typically double the capacity)
2. Re-insert every **active** (non-deleted) entry into the new arrays
   using the new capacity for index calculation
3. Tombstones are naturally cleaned up during rehashing

**Important:** After resizing, the index for a given key changes because
`hash(key) % newCapacity` differs from `hash(key) % oldCapacity`.

---

## Hint 6: Why Prime Capacities Help (Bonus)

**This section is optional enrichment -- you only need basic linear probing for this assignment.**

If you want to go further, try making your capacity always a prime
number. When the hash function has patterns (e.g., many multiples of
some number), a prime capacity ensures that consecutive probes don't
fall into repeating cycles, spreading entries more evenly across the
table. This is optional -- powers of two work fine for this assignment.

**Note on other open addressing techniques:** Linear probing is the
simplest approach, but it can suffer from *primary clustering* -- long
runs of occupied slots that slow down lookups. Other techniques add
variation to the probe sequence to reduce clustering:

- **Quadratic probing:** Instead of checking index+1, index+2, ...,
  check index+1^2, index+2^2, index+3^2, etc. This spreads probes more
  evenly, reducing primary clustering (but can cause *secondary
  clustering* when different keys hash to the same starting index).

- **Double hashing:** Use a second, independent hash function to
  determine the probe step size. E.g., `index = (h1(key) + i * h2(key))
  % capacity`. This virtually eliminates clustering because different
  keys produce different probe sequences.

For this assignment, linear probing is sufficient and keeps the focus
on understanding the core concepts.

---

# Hints -- Question 2: Custom Linked List

These hints are for the linked list operations. Try each method
on your own first before reading ahead.

---

## Hint 1: Maintaining Head and Size

Your list needs two fields: a `head` reference (pointer) to the
first node, and a `size` counter. Every method that adds or removes
a node must update `size`. The `head` starts as null (no nodes yet).

---

## Hint 2: Adding to the End

To append a value, create a new node. If the list is empty (head is
null), the new node becomes the head. Otherwise, walk from the head
to the last node (the one whose `next` is null), then set its `next`
to the new node.

---

## Hint 3: Removing at an Index

Removing the first element (index 0) is a special case -- just update
`head` to point to the second node.

For any other index, walk to the node BEFORE the one you want to
remove (i.e., stop at index - 1). Then "skip over" the target node
by setting `previous.next = previous.next.next`.

Don't forget to return the removed value and decrement the size.

---

## Hint 4: Reversing In-Place

Use three references (pointers): `previous`, `current`, and `next`.
Walk through the list, and at each step:
1. Save `current.next` into `next`
2. Reverse the link: `current.next = previous`
3. Advance: `previous = current`, `current = next`

When done, `previous` is the new head of the reversed list.

---

# Hints -- Question 3: Fibonacci Analysis

These hints are for Part B (analysis questions). Try to trace through
the code by hand before reading ahead.

---

## Hint 1: Drawing the Call Tree

Start from fib(5). It calls fib(4) and fib(3). Then fib(4) calls
fib(3) and fib(2). Keep expanding until you hit base cases (fib(0)
and fib(1)). Draw this as a tree on paper -- each node is one function
call.

---

## Hint 2: Counting Total Calls

Once you have the tree from Hint 1, count every node. Don't forget
to count the root (fib(5) itself) and all the leaf nodes (base cases).

For larger N, notice the recurrence: if T(n) = total calls for fib(n),
then T(n) = 1 + T(n-1) + T(n-2) (the "1" is for the root call itself).

---

## Hint 3: Memoized Call Count

With memoization, the first time fib(k) is called, it recurses normally.
The second time fib(k) is called, it finds the answer already cached
and returns immediately (no further recursion, but it still counts as
one call). Trace through fib(5) keeping track of what's been cached.

---

## Hint 4: Time Complexity

Think about how the TOTAL number of operations scales as N grows:
- If T(5)=15, T(10)=177, T(20)=?, what's the pattern?
- Does the work double when N increases by 1? That's exponential.
- Does the work increase by a constant? That's linear.

---

## Hint 5: Space Complexity

Space is about what EXISTS AT THE SAME TIME, not total allocations:
- For recursion: how deep can the call stack get? (The deepest path.)
- For arrays: how big is the array you allocate?
- For variables: how many variables, regardless of N?

---

# Hints -- Question 4: Factorial Analysis

These hints are for Part B (analysis questions). Try to trace through
the code by hand before reading ahead.

---

## Hint 1: Drawing the Call Tree

Start from fact(5). It calls fact(4). Then fact(4) calls fact(3). Keep
going until you reach the base case fact(0). Draw this as a tree -- but
notice something: unlike Fibonacci, this tree doesn't branch! Each node
has only ONE child.

---

## Hint 2: Counting Total Calls

Once you have the call tree from Hint 1, count every node. The tree is
a straight line, so this is straightforward. For fact(n), how many nodes
are there in total?

For larger N: T(n) = 1 + T(n-1) with T(0) = 1. Solve this recurrence.

---

## Hint 3: Memoized Call Count

With memoization, cached values are returned immediately instead of being
recomputed. But think about this: in the non-memoized version, was any
fact(k) computed more than once? If not, what does memoization actually do?

---

## Hint 4: Time Complexity

Compare factorial's recursion with Fibonacci's recursion:
- Fibonacci: each call spawns TWO recursive calls -> branching tree
- Factorial: each call spawns ??? recursive calls -> what shape?

How does the total work scale with N?

---

## Hint 5: Space Complexity

Same principles as Fibonacci:
- For recursion: how deep is the call stack?
- For arrays: how big is the array?
- For variables: how many, regardless of N?

---

# Hints -- Question 5: Climbing Stairs

These hints reveal a key pattern that makes Climbing Stairs easier to
solve. Try computing a few values by hand before reading ahead.

---

## Hint 1: More Examples

Work out climb(4) and climb(5) by hand:

    climb(4) = 5     (5 ways: [1+1+1+1], [1+1+2], [1+2+1], [2+1+1], [2+2])
    climb(5) = 8

Do you see a pattern in the sequence 1, 2, 3, 5, 8, ...?

---

## Hint 2: The Fibonacci Connection

The number of ways to climb N stairs is the Fibonacci sequence shifted
by one! Specifically:

    ways(n) = ways(n-1) + ways(n-2)

Why? You can reach step N either from step N-1 (one step) or from
step N-2 (two steps), so the total number of ways is the sum of the
ways to reach those two steps.

---

## Hint 3: Reuse What You Know

If you've already solved the Fibonacci problem (Question 3), you can
apply the exact same techniques here: naive recursion, memoization, and
iterative bottom-up. The recurrence is identical -- only the base cases
differ.
