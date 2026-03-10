# Ford-Johnson (Merge-Insertion) Sort

> Reference: D.E. Knuth, *The Art of Computer Programming*, Vol. 3, §5.3.1 — Merge Insertion, p. 184.

---

## Overview

Ford-Johnson is an **optimal comparison sort** for small sequences: it minimises the
worst-case number of comparisons more than any other known algorithm.

It works by combining:
1. **Merge sort** — to recursively sort "winner" elements from each pair.
2. **Binary insertion** — to insert "loser" elements in a clever order that
   keeps the binary search ranges as small as possible.

The key insight is that the insertion order is not left-to-right.  It follows
the **Jacobsthal sequence**, which groups elements so that each group's binary
search range fits exactly within what the previous group already established.

---

## Key Terms

| Term | Meaning |
|------|---------|
| **main chain** | The sequence being built, starting from the sorted larger elements |
| **pend** | The smaller element of each pair — waiting to be inserted |
| **straggler** | The leftover element when `n` is odd |
| **Jacobsthal sequence** | 1, 3, 5, 11, 21, 43, 85, … where $J_n = J_{n-1} + 2 J_{n-2}$ |
| **bound** | The upper limit of the binary search for a pend element |

---

## Algorithm — Step by Step

### Step 1 — Set aside the straggler (if `n` is odd)

If the input has an odd number of elements, remove and save the last one.
It will be inserted at the very end with a normal binary search.

```
n = 21  →  straggler = seq[20],  n = 20
```

---

### Step 2 — Compare consecutive pairs

Scan the sequence in pairs `(seq[0],seq[1])`, `(seq[2],seq[3])`, …
Within each pair, place the **larger** element first.

```
Before:  [a, b]
After:   [max(a,b), min(a,b)]
```

This produces `n/2` pairs.  Store them as `(larger, smaller)`.

---

### Step 3 — Recursively sort the larger elements

Collect all the **larger** elements from every pair and sort them using
Ford-Johnson recursively.  This gives the initial main chain.

```
larger[] = [pairs[0].first, pairs[1].first, …]
sortVec(larger)   ← same algorithm, smaller sub-problem
main chain = sorted larger[]
```

---

### Step 4 — Re-establish pairing

After the recursion, the pairs must be re-linked so that `pairs[i].second`
(the pend element) knows which main-chain element it belongs to.

Sort the pairs **by their first element** — this puts them in the same order
as the now-sorted main chain, so `pairs[i].second` is the pend partner of
`main[i]`.

---

### Step 5 — Jacobsthal-ordered binary insertion

This is the heart of the algorithm.

Build the Jacobsthal sequence up to `k` (number of pairs):

```
k = 10  →  jac = [1, 3, 5, 11]   (stop when jac[last] >= k)
```

Define **groups** from the sequence:

| Group | Range (1-based, inclusive) | Insert order (top → bottom) |
|-------|---------------------------|------------------------------|
| 0 | `[1, 1]` | pend[0] |
| 1 | `[2, 3]` | pend[2], pend[1] |
| 2 | `[4, 5]` | pend[4], pend[3] |
| 3 | `[6, 11]` (capped at k) | pend[9], …, pend[5] |

For each `pend[j]`, the binary search is bounded by the **current position
of `pairs[j].first` in the chain**.  Because `pend[j] < pairs[j].first`
(from Step 2), this is always a valid upper bound.

The top-down insertion order within each group ensures that earlier
insertions don't push the bound rightward for subsequent elements in the
same group.

---

### Step 6 — Insert the straggler

Binary-insert the straggler saved in Step 1 with no bound restriction
(search the entire chain).

---

### Step 7 — Done

The chain is now fully sorted.

---

## Why Jacobsthal Minimises Comparisons

Each binary search of a range of length $m$ costs at most $\lceil \log_2(m+1) \rceil$ comparisons.

The Jacobsthal grouping guarantees that every element inserted in group $g$
searches a range no larger than $J_g$ — and by definition of the sequence,
the sum of $\lceil \log_2(J_g + 1) \rceil$ over all insertions equals the
theoretical minimum.

---

## Worked Example — 21 Elements

### Input

```
[21, 13, 5, 16, 8, 3, 19, 11, 1, 17, 7, 14, 20, 2, 9, 6, 18, 15, 4, 12, 10]
```

---

### Step 1 — Straggler

`n = 21` (odd) → **straggler = 10**, remaining `n = 20`:

```
[21, 13,  5, 16,  8,  3, 19, 11,  1, 17,  7, 14, 20,  2,  9,  6, 18, 15,  4, 12]
```

---

### Step 2 — Pair and sort each pair (larger first)

```
Index:   0       1       2      3       4       5       6      7       8       9
Pair: (21,13) (16, 5) (8, 3) (19,11) (17, 1) (14, 7) (20,2) (9, 6) (18,15) (12, 4)
```

---

### Step 3 — Recursively sort the larger elements

Larger elements: `[21, 16, 8, 19, 17, 14, 20, 9, 18, 12]`

After recursion (Ford-Johnson applied to these 10 elements):

```
main = [8, 9, 12, 14, 16, 17, 18, 19, 20, 21]
```

---

### Step 4 — Sort pairs by their first element to re-establish pairing

```
Index:   0      1      2       3       4       5       6       7       8       9
Pair: (8, 3) (9, 6) (12,4) (14, 7) (16, 5) (17, 1) (18,15) (19,11) (20, 2) (21,13)
```

So:
```
pend = [3, 6, 4, 7, 5, 1, 15, 11, 2, 13]
       [0  1  2  3  4  5   6   7  8   9]   ← index
```

---

### Step 5 — Jacobsthal-ordered insertion

`k = 10` → `jac = [1, 3, 5, 11]`

---

#### Group 0 — insert pend[0] = 3

Bound = position of `pairs[0].first = 8` in chain = position **0**
Binary search in `[0, 0)` → empty → insert at position 0.

```
chain = [3, 8, 9, 12, 14, 16, 17, 18, 19, 20, 21]
```

---

#### Group 1 — insert pend[2] then pend[1] (top-down)

**pend[2] = 4**, bound = position of `pairs[2].first = 12` = position **3**
Binary search in `[3, 8, 9]` (indices 0–2) → 4 goes at position 1.

```
chain = [3, 4, 8, 9, 12, 14, 16, 17, 18, 19, 20, 21]
```

**pend[1] = 6**, bound = position of `pairs[1].first = 9` = position **3**
Binary search in `[3, 4, 8]` (indices 0–2) → 6 goes at position 2.

```
chain = [3, 4, 6, 8, 9, 12, 14, 16, 17, 18, 19, 20, 21]
```

---

#### Group 2 — insert pend[4] then pend[3] (top-down)

**pend[4] = 5**, bound = position of `pairs[4].first = 16` = position **7**
Binary search in `[3, 4, 6, 8, 9, 12, 14]` (indices 0–6) → 5 goes at position 3.

```
chain = [3, 4, 5, 6, 8, 9, 12, 14, 16, 17, 18, 19, 20, 21]
```

**pend[3] = 7**, bound = position of `pairs[3].first = 14` = position **7**
Binary search in `[3, 4, 5, 6, 8, 9, 12]` (indices 0–6) → 7 goes at position 4.

```
chain = [3, 4, 5, 6, 7, 8, 9, 12, 14, 16, 17, 18, 19, 20, 21]
```

---

#### Group 3 — insert pend[9]..pend[5] (top-down, capped at k=10)

**pend[9] = 13**, bound = position of `pairs[9].first = 21` = position **14**
Binary search in indices 0–13 → 13 goes at position 8.

```
chain = [3, 4, 5, 6, 7, 8, 9, 12, 13, 14, 16, 17, 18, 19, 20, 21]
```

**pend[8] = 15**, bound = position of `pairs[8].first = 20` = position **14**
Binary search in indices 0–13 → 15 goes at position 10.

```
chain = [3, 4, 5, 6, 7, 8, 9, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]
```

**pend[7] = 11**, bound = position of `pairs[7].first = 19` = position **14**
Binary search in indices 0–13 → 11 goes at position 7.

```
chain = [3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]
```

**pend[6] = 2**, bound = position of `pairs[6].first = 20` = position **16**
Binary search in indices 0–15 → 2 goes at position 0.

```
chain = [2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]
```

**pend[5] = 1**, bound = position of `pairs[5].first = 17` = position **15**
Binary search in indices 0–14 → 1 goes at position 0.

```
chain = [1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]
```

---

### Step 6 — Insert straggler = 10

Unrestricted binary search → 10 goes at position 9.

```
chain = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]
```

---

### Result

```
Before: 21 13  5 16  8  3 19 11  1 17  7 14 20  2  9  6 18 15  4 12 10
After:   1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21
```

Total binary search bounds used per group:

| Group | Elements inserted | Max search range |
|-------|------------------|-----------------|
| 0 | 1 | 1 |
| 1 | 2 | 3 |
| 2 | 2 | 7 |
| 3 | 5 (capped) | 16 |
| straggler | 1 | 21 |

Each group's bound is at most $J_g$, confirming the Jacobsthal property.
