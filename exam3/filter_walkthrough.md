# Filter Program - Complete Walkthrough

## Example: `echo "abcabc" | ./filter abc`

### Expected Output: `******`

---

## Step-by-Step Execution

### 1. **Program Start - main()**
```
Command: ./filter abc
argc = 2
argv[0] = "./filter"
argv[1] = "abc"
```

**Validation:**
- ✅ argc == 2 (correct number of arguments)
- ✅ argv[1][0] != '\0' (pattern is not empty)

---

### 2. **Initialize Context - init_filter_ctx()**
```c
len = strlen("abc") = 3
```

**After initialization:**
```
filter.pattern = "abc\0"
filter.pattern_len = 3
filter.buffer_size = 0
filter.remaining = 0
filter.buffer = [empty]
```

---

### 3. **First Iteration - Main Loop**

#### 3a. Read Input - filter_read()
```c
bytes_read = read(STDIN, filter.buffer + 0, 4352)
// Reads "abcabc" from stdin
// Returns 6
```

**Buffer state after read:**
```
bytes_read = 6
filter.buffer = ['a','b','c','a','b','c', ... ]
                  0   1   2   3   4   5
```

#### 3b. Update Buffer Size
```c
filter.buffer_size = 0 + 6 = 6
```

#### 3c. Replace Pattern - filter_replace_pattern()

**First search:**
```
search_len = 6
search_start = buffer[0]
memmem(buffer, 6, "abc", 3) → finds "abc" at position 0
```

**Calculate offset:**
```c
offset = buffer[0] - buffer[0] = 0
```

**Replace with asterisks:**
```c
memset(buffer + 0, '*', 3)
```

**Buffer after first replacement:**
```
['*','*','*','a','b','c']
  0   1   2   3   4   5
```

**Update search position:**
```c
next_offset = 0 + 3 = 3
search_len = 6 - 3 = 3
search_start = buffer[3]
```

**Second search:**
```
search_len = 3
search_start = buffer[3]
memmem(buffer+3, 3, "abc", 3) → finds "abc" at position 3
```

**Calculate offset:**
```c
offset = buffer[3] - buffer[0] = 3
```

**Replace with asterisks:**
```c
memset(buffer + 3, '*', 3)
```

**Buffer after second replacement:**
```
['*','*','*','*','*','*']
  0   1   2   3   4   5
```

**Update search position:**
```c
next_offset = 3 + 3 = 6
search_len = 6 - 6 = 0
```

**Loop exits** (search_len < pattern_len)

#### 3d. Write Output - filter_write()
```c
write(STDOUT, buffer, 6) → writes "******"
// Returns 6 (success)
```

**OUTPUT SO FAR: `******`**

#### 3e. Update Remaining - filter_update_remaining()
```c
// Keep last (pattern_len - 1) bytes
remaining = 3 - 1 = 2

// Move last 2 bytes to start
memmove(buffer, buffer + 4, 2)
```

**Buffer after memmove:**
```
['*','*', ... ]
  0   1
filter.remaining = 2
```

---

### 4. **Second Iteration - Main Loop**

#### 4a. Read Input
```c
bytes_read = read(STDIN, buffer + 2, 4350)
// No more data (EOF)
// Returns 0
```

#### 4b. Check EOF
```c
if (bytes_read == 0)
    break;  // Exit loop
```

**Loop exits - no more data to process**

---

### 5. **Program End**
```c
return (0);  // Success
```

**FINAL OUTPUT: `******`** ✅

---

## Key C Concepts Explained

### 1. **Pointers**
```c
char *ptr = buffer;      // ptr points to buffer[0]
char *ptr2 = buffer + 3; // ptr2 points to buffer[3]
size_t offset = ptr2 - ptr; // offset = 3 (pointer arithmetic)
```

### 2. **Structures (struct)**
```c
typedef struct {
    int x;
    float y;
} MyStruct;

MyStruct s;
s.x = 10;           // Access member with dot
MyStruct *ptr = &s;
ptr->x = 20;        // Access through pointer with arrow
```

### 3. **sizeof**
```c
sizeof(char) = 1 byte
sizeof(int) = 4 bytes (typically)
sizeof(buffer) = total array size in bytes
```

### 4. **Type Casting**
```c
(char *)ptr     // Cast pointer to char pointer
(ssize_t)value  // Cast value to signed size type
```

### 5. **Memory Functions**
```c
strlen(s)               // Count chars until '\0'
memcpy(dest, src, n)    // Copy n bytes (no overlap)
memmove(dest, src, n)   // Copy n bytes (handles overlap)
memset(ptr, val, n)     // Set n bytes to val
memmem(hay, hlen, ndl, nlen) // Find ndl in hay
```

### 6. **File Descriptors**
```c
STDIN_FILENO = 0   // Standard input
STDOUT_FILENO = 1  // Standard output
STDERR_FILENO = 2  // Standard error
```

### 7. **Return Values**
```c
read() returns:
  > 0  → number of bytes read
  = 0  → end of file (EOF)
  < 0  → error (check errno)
```

---

## Why Keep "Remaining" Bytes?

### Problem: Pattern Split Across Reads

**Example with pattern "abc":**

**Read 1:** `"hello ab"`
- After processing: no "abc" found
- Keep last 2 bytes: `"ab"`

**Read 2:** `"c world"`
- Buffer starts with: `"ab" + "c world"` = `"abc world"`
- Now we can find and replace "abc"!

**Without remaining bytes:**
- Read 1: `"hello ab"` → no match
- Read 2: `"c world"` → no match
- **MISSED THE PATTERN!** ❌

---

## Common Mistakes to Avoid

1. ❌ `while (i < n) i++` without body → infinite loop if condition wrong
2. ❌ Forgetting `'\0'` terminator for strings
3. ❌ Using `memcpy` with overlapping memory (use `memmove`)
4. ❌ Not checking return values (read, write, malloc can fail!)
5. ❌ Off-by-one errors in array indexing
6. ❌ Forgetting to cast pointer types when doing arithmetic

---

## Testing Your Understanding

Try these test cases:
```bash
echo "abcdefabc" | ./filter abc
# Expected: ***def***

echo "ababcabababc" | ./filter ababc
# Expected: *****ab*****

echo "hello" | ./filter xyz
# Expected: hello

echo "" | ./filter abc
# Expected: (empty output)
```
