# PROJ2T1 Hash Table Exercise

## Overview

Implement a hash table for strings in C++ using open addressing with linear probing. Your implementation must support insertion, lookup, erasing, and resizing. Important: do NOT use deleted flags. When an element is removed, you must fill the emptied slot by moving successive elements so that probe sequences remain correct.

## Implementation details

- Collision resolution: **open addressing** with **linear probing** (probe sequence: index, index+1, index+2, ... modulo capacity).
- Initial capacity: 16
- Load factor threshold: 0.5 (i.e., trigger rehashing if `(double)size/capacity > 0.5` after a successful insertion).
- Rehashing: when resizing, **double** the capacity and reinsert all existing entries **in the order of their index in the old table**.
- Hash function: use `std::hash<std::string>` for keys (i.e., `std::hash<std::string>{}(key) % capacity` for slot index).
- Removal must **not use a separate `deleted` flag**; it must shift some successive elements to fill the gap until you encounter an empty slot.

## Input format

The input contains multiple lines, and each line stands for an operation: (`KEY` is a string including `'a'-'z'` of length $\le 10$.)
- `1 KEY`: insert `KEY`.
- `2 KEY`: find `KEY`.
- `3 KEY`: erase `KEY`.
- `0`: input terminates.

It is ensured that number of operations $\le 2\times 10^5$.

## Output format

The output format is different among these operations:
- For inserting `KEY`:
  - If `KEY` already exists, print `KEY already exists at IDX`, where `IDX` is the index of `KEY` in the table.
  - Otherwise, print `KEY inserted at IDX`.
- For finding `KEY`.
  - If `KEY` does not exist, print `KEY does not exist`.
  - Otherwise, print `KEY found at IDX`.
- For erasing `KEY`.
  - If `KEY` does not exist, print `KEY does not exist`.
  - Otherwise, print one or more lines to show the complete steps of moving successive elements like
    ```
    KEY erased at IDX, moving KEY_1 from IDX_1, moving KEY_2 from IDX_2, ..., moving KEY_X from IDX_X
    ```

## Grading rubric

20pts for this problem, 5pts for each subtask:

- Subtask 1: tiny tests, no insertion will trigger rehashing.
- Subtask 2: only insertion, no finding and erasing.
- Subtask 3: only insertion and finding, no erasing.
- Subtask 4: full tests.



## Compile Directive

```powershell
g++ foo.cc -o foo -O2 -std=c++17 -Wall -Wpedantic -Wextra -Werror -fmax-errors=3 -fsanitize=undefined -fsanitize=address -DONLINE_JUDGE -fdiagnostics-color=always
```
