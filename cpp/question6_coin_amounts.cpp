/**
 * ===============================================================
 *  PROBLEM 6 -- Coin Combination Amounts: Three Implementations
 * ===============================================================
 *
 *  You have an unlimited supply of pennies (1 cent), nickels (5 cents),
 *  dimes (10 cents), and quarters (25 cents).
 *
 *  Given an integer N representing the number of coins you can use,
 *  find how many DISTINCT total amounts (in cents) can be formed
 *  using 0 to N coins.
 *
 *  For example, with N=2 coins:
 *    - 0 coins: amount = 0
 *    - 1 coin:  amounts = 1, 5, 10, 25
 *    - 2 coins: amounts = 2, 6, 10, 11, 15, 20, 25, 26, 30, 35, 50
 *    Distinct amounts = {0, 1, 2, 5, 6, 10, 11, 15, 20, 25, 26, 30, 35, 50}
 *    Answer = 14
 *
 *  Note: the same amount can be formed different ways (e.g., 6 = 1+5
 *  or 5+1) but counts only once.
 *
 *  Your task: implement three different approaches to count distinct amounts.
 *
 *  --- Approach 1: Naive Recursive --------------------------------
 *
 *  Explore every possible coin choice at each step using DFS.
 *  Collect all reachable amounts in an unordered_set.
 *  Simple but EXPONENTIAL -- O(4^N) time!
 *
 *  Why so slow? With 4 coin choices at each of N steps, the call
 *  tree has up to 4^N leaves. Many (coinsLeft, amount) states are
 *  visited multiple times via different coin sequences.
 *
 *  Partial call tree for N=2:
 *
 *    explore(left=2, amt=0)
 *    |-- explore(left=1, amt=1)    [+1]
 *    |   |-- explore(left=0, amt=2)    [+1]
 *    |   |-- explore(left=0, amt=6)    [+5]
 *    |   |-- explore(left=0, amt=11)   [+10]
 *    |   +-- explore(left=0, amt=26)   [+25]
 *    |-- explore(left=1, amt=5)    [+5]
 *    |   |-- explore(left=0, amt=6)    <- DUPLICATE state!
 *    |   |-- explore(left=0, amt=10)
 *    |   +-- ...
 *    |-- explore(left=1, amt=10)   [+10]
 *    |   +-- ...
 *    +-- explore(left=1, amt=25)   [+25]
 *        +-- ...
 *
 *  N=5: ~1365 calls. N=10: ~1.4 million. N=20: ~1.4 trillion!
 *
 *  --- Approach 2: Memoized (Top-Down DP) -------------------------
 *
 *  Same recursive structure, but track visited (coinsLeft, amount)
 *  pairs to avoid re-exploring states already seen.
 *  Total states: at step k, max amount is 25*k, so total states
 *  are roughly N * 25*N = O(N^2). Each state does O(4) work.
 *  Overall: O(N^2) time, O(N^2) space.
 *
 *  --- Approach 3: Iterative (Bottom-Up DP) -----------------------
 *
 *  Use a boolean vector reachable[0..25*N].
 *  Start with reachable[0] = true.
 *  For each of N steps, expand reachable amounts by trying each coin.
 *  O(N * 25*N * 4) = O(N^2) time, O(N) space.
 *  No recursion -- the most efficient approach.
 *
 *  Compile & run:
 *    g++ -std=c++17 -O2 question6_coin_amounts.cpp -o q6 && ./q3
 *    cl /std:c++17 /EHsc /O2 question6_coin_amounts.cpp /Fe:q3.exe && q3.exe
 * ===============================================================
 */

#include "test_harness.h"
#include <unordered_set>
#include <vector>

int solveRecursive(int n) {
    // TODO: Implement naive recursive solution
    // Build an unordered_set of all reachable amounts by exploring every coin choice
    // Hint: Use a helper function explore(set, coinsLeft, currentAmount)
    //       Base: always insert currentAmount into the set
    //       Recurse: if coinsLeft > 0, try each coin {1, 5, 10, 25}
    // Return the size of the set
    return -1;
}

int solveMemoized(int n) {
    // TODO: Implement top-down DP with memoization
    // Same recursive idea, but track visited (coinsLeft, amount) pairs
    // to skip states you've already explored
    // Hint: Use a vector<vector<bool>> visited of size (n+1) x (25*n+1)
    return -1;
}

int solveIterative(int n) {
    // TODO: Implement bottom-up DP (iterative)
    // Use a vector<bool> reachable of size 25*n+1
    // Start with reachable[0] = true
    // For each step, expand reachable amounts by trying each coin
    return -1;
}

#include "question6_tests.h"

int main() {
    auto h = q6_tests::newHarness();
    bool passed = q6_tests::addTests(h, solveRecursive, solveMemoized, solveIterative)
        .run();   // Tip: change to .runQuick() for faster feedback
    return passed ? 0 : 1;
}
