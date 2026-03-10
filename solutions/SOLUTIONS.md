# Solution Key

---

## Question 1 -- Custom HashMap (Open Addressing with Dynamic Resizing)

### Java

\\java
public void put(int key, int value) {
    if ((double)(size + 1) / capacity > MAX_LOAD_FACTOR) {
        resize();
    }
    int startIndex = hash(key) % capacity;
    int firstTombstone = -1;
    int i = startIndex;
    while (true) {
        if (!occupied[i]) {
            int insertAt = (firstTombstone != -1) ? firstTombstone : i;
            keys[insertAt] = key;
            values[insertAt] = value;
            occupied[insertAt] = true;
            deleted[insertAt] = false;
            size++;
            return;
        }
        if (deleted[i]) {
            if (firstTombstone == -1) {
                firstTombstone = i;
            }
        } else if (keys[i] == key) {
            values[i] = value;
            return;
        }
        i = (i + 1) % capacity;
        if (i == startIndex) {
            break;
        }
    }
    if (firstTombstone != -1) {
        keys[firstTombstone] = key;
        values[firstTombstone] = value;
        deleted[firstTombstone] = false;
        size++;
    }
}

public int get(int key) {
    int startIndex = hash(key) % capacity;
    int i = startIndex;
    while (occupied[i]) {
        if (!deleted[i] && keys[i] == key) {
            return values[i];
        }
        i = (i + 1) % capacity;
        if (i == startIndex) {
            break;
        }
    }
    return -1;
}

public boolean remove(int key) {
    int startIndex = hash(key) % capacity;
    int i = startIndex;
    while (occupied[i]) {
        if (!deleted[i] && keys[i] == key) {
            deleted[i] = true;
            size--;
            return true;
        }
        i = (i + 1) % capacity;
        if (i == startIndex) {
            break;
        }
    }
    return false;
}

public boolean containsKey(int key) {
    return get(key) != -1;
}

public int size() {
    return size;
}

private void resize() {
    int newCapacity = capacity * 2;
    int[] oldKeys = keys;
    int[] oldValues = values;
    boolean[] oldOccupied = occupied;
    boolean[] oldDeleted = deleted;
    int oldCapacity = capacity;

    capacity = newCapacity;
    keys = new int[capacity];
    values = new int[capacity];
    occupied = new boolean[capacity];
    deleted = new boolean[capacity];
    size = 0;

    for (int j = 0; j < oldCapacity; j++) {
        if (oldOccupied[j] && !oldDeleted[j]) {
            put(oldKeys[j], oldValues[j]);
        }
    }
}
\
### Python

\\python
def put(self, key, value):
    if (self._size + 1) / self._capacity > self.MAX_LOAD_FACTOR:
        self._resize()
    start = self._hash(key) % self._capacity
    first_tomb = -1
    i = start
    while True:
        if not self._occupied[i]:
            at = first_tomb if first_tomb != -1 else i
            self._keys[at] = key
            self._values[at] = value
            self._occupied[at] = True
            self._deleted[at] = False
            self._size += 1
            return
        if self._deleted[i]:
            if first_tomb == -1:
                first_tomb = i
        elif self._keys[i] == key:
            self._values[i] = value
            return
        i = (i + 1) % self._capacity
        if i == start:
            break
    if first_tomb != -1:
        self._keys[first_tomb] = key
        self._values[first_tomb] = value
        self._deleted[first_tomb] = False
        self._size += 1

def get(self, key):
    start = self._hash(key) % self._capacity
    i = start
    while self._occupied[i]:
        if not self._deleted[i] and self._keys[i] == key:
            return self._values[i]
        i = (i + 1) % self._capacity
        if i == start:
            break
    return -1

def remove(self, key):
    start = self._hash(key) % self._capacity
    i = start
    while self._occupied[i]:
        if not self._deleted[i] and self._keys[i] == key:
            self._deleted[i] = True
            self._size -= 1
            return True
        i = (i + 1) % self._capacity
        if i == start:
            break
    return False

def contains_key(self, key):
    return self.get(key) != -1

def size(self):
    return self._size

def _resize(self):
    old_keys = self._keys
    old_values = self._values
    old_occupied = self._occupied
    old_deleted = self._deleted
    old_cap = self._capacity

    self._capacity *= 2
    self._keys = [0] * self._capacity
    self._values = [0] * self._capacity
    self._occupied = [False] * self._capacity
    self._deleted = [False] * self._capacity
    self._size = 0

    for j in range(old_cap):
        if old_occupied[j] and not old_deleted[j]:
            self.put(old_keys[j], old_values[j])
\
### C++

\\cpp
void put(int key, int value) {
    if ((double)(_size + 1) / _capacity > MAX_LOAD_FACTOR) {
        resize();
    }
    int startIndex = hash(key) % _capacity;
    int firstTombstone = -1;
    int i = startIndex;
    while (true) {
        if (!_occupied[i]) {
            int at = (firstTombstone != -1) ? firstTombstone : i;
            _keys[at] = key;
            _values[at] = value;
            _occupied[at] = true;
            _deleted[at] = false;
            _size++;
            return;
        }
        if (_deleted[i]) {
            if (firstTombstone == -1) {
                firstTombstone = i;
            }
        } else if (_keys[i] == key) {
            _values[i] = value;
            return;
        }
        i = (i + 1) % _capacity;
        if (i == startIndex) {
            break;
        }
    }
    if (firstTombstone != -1) {
        _keys[firstTombstone] = key;
        _values[firstTombstone] = value;
        _deleted[firstTombstone] = false;
        _size++;
    }
}

int get(int key) const {
    int startIndex = hash(key) % _capacity;
    int i = startIndex;
    while (_occupied[i]) {
        if (!_deleted[i] && _keys[i] == key) {
            return _values[i];
        }
        i = (i + 1) % _capacity;
        if (i == startIndex) {
            break;
        }
    }
    return -1;
}

bool remove(int key) {
    int startIndex = hash(key) % _capacity;
    int i = startIndex;
    while (_occupied[i]) {
        if (!_deleted[i] && _keys[i] == key) {
            _deleted[i] = true;
            _size--;
            return true;
        }
        i = (i + 1) % _capacity;
        if (i == startIndex) {
            break;
        }
    }
    return false;
}

bool containsKey(int key) const {
    return get(key) != -1;
}

int size() const {
    return _size;
}

void resize() {
    int newCap = _capacity * 2;
    std::vector<int> oldKeys = _keys;
    std::vector<int> oldValues = _values;
    std::vector<bool> oldOccupied = _occupied;
    std::vector<bool> oldDeleted = _deleted;
    int oldCap = _capacity;

    _capacity = newCap;
    _keys.assign(newCap, 0);
    _values.assign(newCap, 0);
    _occupied.assign(newCap, false);
    _deleted.assign(newCap, false);
    _size = 0;

    for (int j = 0; j < oldCap; j++) {
        if (oldOccupied[j] && !oldDeleted[j]) {
            put(oldKeys[j], oldValues[j]);
        }
    }
}
\
## Question 2 -- Fibonacci: Four Implementations + Analysis

### Part A ╬ô├ç├╢ Code Implementations

#### Java

```java
public static long fibRecursive(int n) {
    if (n <= 0) { return 0; }
    if (n == 1) { return 1; }
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

public static long fibMemoized(int n) {
    if (n <= 0) { return 0; }
    long[] memo = new long[n + 1];
    for (int i = 0; i <= n; i++) { memo[i] = -1; }
    return fibMemoHelper(n, memo);
}

private static long fibMemoHelper(int n, long[] memo) {
    if (n <= 0) { return 0; }
    if (n == 1) { return 1; }
    if (memo[n] != -1) { return memo[n]; }
    memo[n] = fibMemoHelper(n - 1, memo) + fibMemoHelper(n - 2, memo);
    return memo[n];
}

public static long fibBottomUp(int n) {
    if (n <= 0) { return 0; }
    if (n == 1) { return 1; }
    long[] dp = new long[n + 1];
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

public static long fibIterative(int n) {
    if (n <= 0) { return 0; }
    if (n == 1) { return 1; }
    long prev = 0;
    long curr = 1;
    for (int i = 2; i <= n; i++) {
        long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}
```

#### Python

```python
def fib_recursive(n):
    if n <= 0:
        return 0
    if n == 1:
        return 1
    return fib_recursive(n - 1) + fib_recursive(n - 2)

def fib_memoized(n):
    memo = {}
    def helper(k):
        if k <= 0:
            return 0
        if k == 1:
            return 1
        if k in memo:
            return memo[k]
        memo[k] = helper(k - 1) + helper(k - 2)
        return memo[k]
    return helper(n)

def fib_bottom_up(n):
    if n <= 0:
        return 0
    if n == 1:
        return 1
    dp = [0] * (n + 1)
    dp[0] = 0
    dp[1] = 1
    for i in range(2, n + 1):
        dp[i] = dp[i - 1] + dp[i - 2]
    return dp[n]

def fib_iterative(n):
    if n <= 0:
        return 0
    if n == 1:
        return 1
    prev, curr = 0, 1
    for _ in range(2, n + 1):
        prev, curr = curr, prev + curr
    return curr
```

#### C++

```cpp
long long fibRecursive(int n) {
    if (n <= 0) { return 0; }
    if (n == 1) { return 1; }
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

long long fibMemoHelper(int n, std::vector<long long>& memo) {
    if (n <= 0) { return 0; }
    if (n == 1) { return 1; }
    if (memo[n] != -1) { return memo[n]; }
    memo[n] = fibMemoHelper(n - 1, memo) + fibMemoHelper(n - 2, memo);
    return memo[n];
}

long long fibMemoized(int n) {
    if (n <= 0) { return 0; }
    std::vector<long long> memo(n + 1, -1);
    return fibMemoHelper(n, memo);
}

long long fibBottomUp(int n) {
    if (n <= 0) { return 0; }
    if (n == 1) { return 1; }
    std::vector<long long> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}

long long fibIterative(int n) {
    if (n <= 0) { return 0; }
    if (n == 1) { return 1; }
    long long prev = 0;
    long long curr = 1;
    for (int i = 2; i <= n; i++) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}
```

### Part B ╬ô├ç├╢ Analysis Answers

| # | Question | Answer |
|---|----------|--------|
| B1 | Call counts for fibRecursive(5): `[fib(0), fib(1), ..., fib(5)]` | `[3, 5, 3, 2, 1, 1]` |
| B2 | Total calls for fibRecursive(5) | **15** |
| B3 | Total calls for fibRecursive(10) | **177** |
| B4 | Total calls for fibMemoized(5) | **9** |
| B5 | Time complexity of fibRecursive | **O(2^N)** |
| B6 | Space complexity of fibRecursive | **O(N)** |
| B7 | Time complexity of fibMemoized | **O(N)** |
| B8 | Space complexity of fibMemoized | **O(N)** |
| B9 | Time complexity of fibBottomUp | **O(N)** |
| B10 | Space complexity of fibBottomUp | **O(N)** |
| B11 | Time complexity of fibIterative | **O(N)** |
| B12 | Space complexity of fibIterative | **O(1)** |

---

## Question 3 -- Coin Combination Amounts: Three Implementations

### Java

```java
// --- Approach 1: Naive Recursive ---
public static int solveRecursive(int n) {
    Set<Integer> amounts = new HashSet<>();
    explore(amounts, n, 0);
    return amounts.size();
}

private static void explore(Set<Integer> amounts, int coinsLeft, int currentAmount) {
    amounts.add(currentAmount);
    if (coinsLeft > 0) {
        for (int c : new int[]{1, 5, 10, 25}) {
            explore(amounts, coinsLeft - 1, currentAmount + c);
        }
    }
}

// --- Approach 2: Memoized (Top-Down DP) ---
public static int solveMemoized(int n) {
    Set<Integer> amounts = new HashSet<>();
    boolean[][] visited = new boolean[n + 1][25 * n + 1];
    exploreMemo(amounts, visited, n, 0);
    return amounts.size();
}

private static void exploreMemo(Set<Integer> amounts, boolean[][] visited,
                                int coinsLeft, int currentAmount) {
    if (visited[coinsLeft][currentAmount]) { return; }
    visited[coinsLeft][currentAmount] = true;
    amounts.add(currentAmount);
    if (coinsLeft > 0) {
        for (int c : new int[]{1, 5, 10, 25}) {
            if (currentAmount + c <= visited[0].length - 1) {
                exploreMemo(amounts, visited, coinsLeft - 1, currentAmount + c);
            }
        }
    }
}

// --- Approach 3: Iterative (Bottom-Up DP) ---
public static int solveIterative(int n) {
    if (n == 0) { return 1; }
    int maxAmount = 25 * n;
    boolean[] reachable = new boolean[maxAmount + 1];
    reachable[0] = true;
    for (int step = 0; step < n; step++) {
        boolean[] next = new boolean[maxAmount + 1];
        for (int amt = 0; amt <= maxAmount; amt++) {
            if (reachable[amt]) {
                for (int c : new int[]{1, 5, 10, 25}) {
                    if (amt + c <= maxAmount) {
                        next[amt + c] = true;
                    }
                }
            }
        }
        for (int amt = 0; amt <= maxAmount; amt++) {
            if (next[amt]) {
                reachable[amt] = true;
            }
        }
    }
    int count = 0;
    for (boolean b : reachable) {
        if (b) { count++; }
    }
    return count;
}
```

### Python

```python
# --- Approach 1: Naive Recursive ---
def solve_recursive(n):
    amounts = set()
    def explore(coins_left, current_amount):
        amounts.add(current_amount)
        if coins_left > 0:
            for c in [1, 5, 10, 25]:
                explore(coins_left - 1, current_amount + c)
    explore(n, 0)
    return len(amounts)

# --- Approach 2: Memoized (Top-Down DP) ---
def solve_memoized(n):
    amounts = set()
    visited = set()
    def explore(coins_left, current_amount):
        state = (coins_left, current_amount)
        if state in visited:
            return
        visited.add(state)
        amounts.add(current_amount)
        if coins_left > 0:
            for c in [1, 5, 10, 25]:
                explore(coins_left - 1, current_amount + c)
    explore(n, 0)
    return len(amounts)

# --- Approach 3: Iterative (Bottom-Up DP) ---
def solve_iterative(n):
    if n == 0:
        return 1
    max_amount = 25 * n
    reachable = [False] * (max_amount + 1)
    reachable[0] = True
    for _ in range(n):
        next_reach = [False] * (max_amount + 1)
        for amt in range(max_amount + 1):
            if reachable[amt]:
                for c in [1, 5, 10, 25]:
                    if amt + c <= max_amount:
                        next_reach[amt + c] = True
        for amt in range(max_amount + 1):
            if next_reach[amt]:
                reachable[amt] = True
    return sum(reachable)
```

### C++

```cpp
// --- Approach 1: Naive Recursive ---
void exploreRec(std::unordered_set<int>& amounts, int coinsLeft, int currentAmount) {
    amounts.insert(currentAmount);
    if (coinsLeft > 0) {
        for (int c : {1, 5, 10, 25}) {
            exploreRec(amounts, coinsLeft - 1, currentAmount + c);
        }
    }
}

int solveRecursive(int n) {
    std::unordered_set<int> amounts;
    exploreRec(amounts, n, 0);
    return static_cast<int>(amounts.size());
}

// --- Approach 2: Memoized (Top-Down DP) ---
void exploreMemo(std::unordered_set<int>& amounts,
                 std::vector<std::vector<bool>>& visited,
                 int coinsLeft, int currentAmount) {
    if (visited[coinsLeft][currentAmount]) { return; }
    visited[coinsLeft][currentAmount] = true;
    amounts.insert(currentAmount);
    if (coinsLeft > 0) {
        for (int c : {1, 5, 10, 25}) {
            if (currentAmount + c < (int)visited[0].size()) {
                exploreMemo(amounts, visited, coinsLeft - 1, currentAmount + c);
            }
        }
    }
}

int solveMemoized(int n) {
    std::unordered_set<int> amounts;
    std::vector<std::vector<bool>> visited(n + 1, std::vector<bool>(25 * n + 1, false));
    exploreMemo(amounts, visited, n, 0);
    return static_cast<int>(amounts.size());
}

// --- Approach 3: Iterative (Bottom-Up DP) ---
int solveIterative(int n) {
    if (n == 0) { return 1; }
    int maxAmount = 25 * n;
    std::vector<bool> reachable(maxAmount + 1, false);
    reachable[0] = true;
    for (int step = 0; step < n; step++) {
        std::vector<bool> next(maxAmount + 1, false);
        for (int amt = 0; amt <= maxAmount; amt++) {
            if (reachable[amt]) {
                for (int c : {1, 5, 10, 25}) {
                    if (amt + c <= maxAmount) {
                        next[amt + c] = true;
                    }
                }
            }
        }
        for (int amt = 0; amt <= maxAmount; amt++) {
            if (next[amt]) { reachable[amt] = true; }
        }
    }
    int count = 0;
    for (int amt = 0; amt <= maxAmount; amt++) {
        if (reachable[amt]) { count++; }
    }
    return count;
}
```

---

## Question 4 -- Climbing Stairs: Three Implementations

### Java

```java
// --- Approach 1: Naive Recursive ---
public static long solveRecursive(int n) {
    if (n <= 1) { return 1; }
    if (n == 2) { return 2; }
    return solveRecursive(n - 1) + solveRecursive(n - 2);
}

// --- Approach 2: Memoized (Top-Down DP) ---
public static long solveMemoized(int n) {
    if (n <= 1) { return 1; }
    long[] memo = new long[n + 1];
    for (int i = 0; i <= n; i++) { memo[i] = -1; }
    return memoHelper(n, memo);
}

private static long memoHelper(int n, long[] memo) {
    if (n <= 1) { return 1; }
    if (n == 2) { return 2; }
    if (memo[n] != -1) { return memo[n]; }
    memo[n] = memoHelper(n - 1, memo) + memoHelper(n - 2, memo);
    return memo[n];
}

// --- Approach 3: Iterative (Bottom-Up DP) ---
public static long solveIterative(int n) {
    if (n <= 1) { return 1; }
    long prev = 1;
    long curr = 2;
    for (int i = 3; i <= n; i++) {
        long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}
```

### Python

```python
# --- Approach 1: Naive Recursive ---
def solve_recursive(n):
    if n <= 1:
        return 1
    if n == 2:
        return 2
    return solve_recursive(n - 1) + solve_recursive(n - 2)

# --- Approach 2: Memoized (Top-Down DP) ---
def solve_memoized(n):
    memo = {}
    def helper(k):
        if k <= 1:
            return 1
        if k == 2:
            return 2
        if k in memo:
            return memo[k]
        memo[k] = helper(k - 1) + helper(k - 2)
        return memo[k]
    return helper(n)

# --- Approach 3: Iterative (Bottom-Up DP) ---
def solve_iterative(n):
    if n <= 1:
        return 1
    prev, curr = 1, 2
    for _ in range(3, n + 1):
        prev, curr = curr, prev + curr
    return curr
```

### C++

```cpp
// --- Approach 1: Naive Recursive ---
long long solveRecursive(int n) {
    if (n <= 1) { return 1; }
    if (n == 2) { return 2; }
    return solveRecursive(n - 1) + solveRecursive(n - 2);
}

// --- Approach 2: Memoized (Top-Down DP) ---
long long memoHelper(int n, std::vector<long long>& memo) {
    if (n <= 1) { return 1; }
    if (n == 2) { return 2; }
    if (memo[n] != -1) { return memo[n]; }
    memo[n] = memoHelper(n - 1, memo) + memoHelper(n - 2, memo);
    return memo[n];
}

long long solveMemoized(int n) {
    if (n <= 1) { return 1; }
    std::vector<long long> memo(n + 1, -1);
    return memoHelper(n, memo);
}

// --- Approach 3: Iterative (Bottom-Up DP) ---
long long solveIterative(int n) {
    if (n <= 1) { return 1; }
    long long prev = 1, curr = 2;
    for (int i = 3; i <= n; i++) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}
```

---

## Question 5 -- Custom Linked List

### Java

```java
static class CustomLinkedList {
    private Node head;
    private int count;

    public CustomLinkedList() {
        this.head = null;
        this.count = 0;
    }

    public void add(int value) {
        Node newNode = new Node(value);
        if (head == null) {
            head = newNode;
        } else {
            Node curr = head;
            while (curr.next != null) {
                curr = curr.next;
            }
            curr.next = newNode;
        }
        count++;
    }

    public int get(int index) {
        if (index < 0 || index >= count) {
            throw new IndexOutOfBoundsException("Index: " + index);
        }
        Node curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr.next;
        }
        return curr.value;
    }

    public int remove(int index) {
        if (index < 0 || index >= count) {
            throw new IndexOutOfBoundsException("Index: " + index);
        }
        int val;
        if (index == 0) {
            val = head.value;
            head = head.next;
        } else {
            Node prev = head;
            for (int i = 0; i < index - 1; i++) {
                prev = prev.next;
            }
            val = prev.next.value;
            prev.next = prev.next.next;
        }
        count--;
        return val;
    }

    public boolean contains(int value) {
        Node curr = head;
        while (curr != null) {
            if (curr.value == value) {
                return true;
            }
            curr = curr.next;
        }
        return false;
    }

    public int size() {
        return count;
    }

    public void reverse() {
        Node prev = null;
        Node curr = head;
        while (curr != null) {
            Node next = curr.next;
            curr.next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }
}
```

### Python

```python
class CustomLinkedList:

    def __init__(self):
        self.head = None
        self.count = 0

    def add(self, value):
        new_node = Node(value)
        if self.head is None:
            self.head = new_node
        else:
            curr = self.head
            while curr.next is not None:
                curr = curr.next
            curr.next = new_node
        self.count += 1

    def get(self, index):
        if index < 0 or index >= self.count:
            raise IndexError(f"Index: {index}")
        curr = self.head
        for _ in range(index):
            curr = curr.next
        return curr.value

    def remove(self, index):
        if index < 0 or index >= self.count:
            raise IndexError(f"Index: {index}")
        if index == 0:
            val = self.head.value
            self.head = self.head.next
        else:
            prev = self.head
            for _ in range(index - 1):
                prev = prev.next
            val = prev.next.value
            prev.next = prev.next.next
        self.count -= 1
        return val

    def contains(self, value):
        curr = self.head
        while curr is not None:
            if curr.value == value:
                return True
            curr = curr.next
        return False

    def size(self):
        return self.count

    def reverse(self):
        prev = None
        curr = self.head
        while curr is not None:
            next_node = curr.next
            curr.next = prev
            prev = curr
            curr = next_node
        self.head = prev
```

### C++

```cpp
class CustomLinkedList {
public:
    Node* head;
    int count;

    CustomLinkedList() : head(nullptr), count(0) {}

    ~CustomLinkedList() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
        }
    }

    void add(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = newNode;
        }
        count++;
    }

    int get(int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index: " + std::to_string(index));
        }
        Node* curr = head;
        for (int i = 0; i < index; i++) {
            curr = curr->next;
        }
        return curr->value;
    }

    int remove(int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index: " + std::to_string(index));
        }
        int val;
        if (index == 0) {
            val = head->value;
            Node* old = head;
            head = head->next;
            delete old;
        } else {
            Node* prev = head;
            for (int i = 0; i < index - 1; i++) {
                prev = prev->next;
            }
            Node* target = prev->next;
            val = target->value;
            prev->next = target->next;
            delete target;
        }
        count--;
        return val;
    }

    bool contains(int value) {
        Node* curr = head;
        while (curr != nullptr) {
            if (curr->value == value) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    int size() {
        return count;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        while (curr != nullptr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }
};
```
