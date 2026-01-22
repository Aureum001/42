# Level 2 Study Guide - Parser Exercises

## Core Pattern: Recursive Descent Parser

Both `argo` and `vbc` use the same technique called **recursive descent parsing**.

### Essential Concepts (Study in Order):

#### 1. **Token Peeking** (Read without consuming)
```c
int peek(FILE *stream) {
    int c = getc(stream);  // Read character
    ungetc(c, stream);     // Put it back!
    return c;              // Return what we saw
}
```
**Why?** Look ahead to decide what to parse next without losing the character.

#### 2. **Token Accepting** (Conditionally consume)
```c
int accept(FILE *stream, char c) {
    if (peek(stream) == c) {
        getc(stream);  // Consume it
        return 1;      // Success
    }
    return 0;          // Not the character we wanted
}
```
**Why?** Try to match a character, consume if match, skip if not.

#### 3. **Token Expecting** (Must consume or error)
```c
int expect(FILE *stream, char c) {
    if (!accept(stream, c)) {
        unexpected(stream);  // Error!
        return 0;
    }
    return 1;
}
```
**Why?** We MUST see this character or the syntax is invalid.

### The Big Picture - Grammar Rules

#### ARGO (JSON Parser):
```
value     → map | integer | string
map       → '{' pairs '}'
pairs     → pair (',' pair)*
pair      → string ':' value
string    → '"' characters '"'
integer   → digits
```

#### VBC (Math Parser):
```
expression → term (('+') term)*
term       → factor (('*') factor)*
factor     → digit | '(' expression ')'
```

## Study Strategy:

### Phase 1: Understand the Building Blocks (30 min)
1. Read `peek()`, `accept()`, `expect()` - these are your tools
2. Understand the data structures (json struct, pair struct)
3. Trace through parsing a simple number: `"42"`

### Phase 2: Follow One Complete Path (1 hour)
Pick ONE example and trace EVERY function call:

**For ARGO:** Trace `'{"a":1}'`
```
argo() → parser() → parse_map()
  ↓
  expect('{')
  ↓
  parse string "a" → key
  ↓
  expect(':')
  ↓
  parser() → parse_int() → value
  ↓
  expect('}')
```

**For VBC:** Trace `'2+3'`
```
expression()
  ↓
  term() → factor() → get '2'
  ↓
  accept('+') → yes!
  ↓
  term() → factor() → get '3'
  ↓
  return 2 + 3 = 5
```

### Phase 3: Identify the Pattern (30 min)
Notice the recursive structure:
- **Simple case**: Direct parse (digit, simple string)
- **Compound case**: Call other parsers (map contains values, expression contains terms)
- **Always check**: peek → decide → parse → repeat

### Phase 4: Practice Small Pieces (1-2 hours)
Don't write the whole thing! Practice:

1. **Write just the number parser**
   ```c
   int parse_int(json *dst, FILE *stream) {
       // Read digits, convert to int
   }
   ```

2. **Write just the string parser**
   ```c
   char *get_str(FILE *stream) {
       // Handle quotes and escaping
   }
   ```

3. **Write just the factor (for vbc)**
   ```c
   int factor(char **str) {
       // Parse digit or (expression)
   }
   ```

### Phase 5: Understand Recursion (Critical!)
```c
// This is the magic - functions call each other!

int parser(json *dst, FILE *stream) {
    if (peek(stream) == '{')
        return parse_map(dst, stream);  // ← Will call parser() again!
    // ...
}

int parse_map(json *dst, FILE *stream) {
    // ...
    parser(&value, stream);  // ← Recursive call!
    // ...
}
```

**Why it works:**
- `{"a":{"b":1}}` → parse_map calls parser → parser calls parse_map → etc.
- Base case: eventually hit a number or string (no more recursion)

## Quick Reference - Common Patterns

### Pattern 1: Parse List (comma-separated)
```c
while (1) {
    parse_item();
    if (!accept(','))
        break;
}
```

### Pattern 2: Parse with Operators
```c
int result = parse_first();
while (accept('+')) {
    result += parse_next();
}
return result;
```

### Pattern 3: Handle Escaping
```c
if (c == '\\') {
    c = getc(stream);  // Get next char
    // Handle \", \\, etc.
}
```

## Time Management for Exam

Level 2 exercises take **2-3 hours minimum**. Budget:
- 30 min: Understand the problem and grammar
- 60 min: Write helper functions (peek, accept, simple parsers)
- 60 min: Write main recursive parsers
- 30 min: Debug and test

## Key Debugging Tips

1. **Print what you're parsing:**
   ```c
   printf("Parsing char: '%c'\n", peek(stream));
   ```

2. **Track recursion depth:**
   ```c
   static int depth = 0;
   depth++;
   printf("%*sParsing map\n", depth*2, "");
   // ... parse ...
   depth--;
   ```

3. **Test incrementally:**
   - First: parse just numbers
   - Then: parse just strings
   - Then: parse empty map `{}`
   - Then: parse map with one item
   - Finally: nested structures

## Common Mistakes to Avoid

1. ❌ Forgetting to consume the character after peek
2. ❌ Not handling EOF properly
3. ❌ Memory leaks (forgot to free on error)
4. ❌ Wrong recursion (infinite loop)
5. ❌ Not checking return values

## The "Aha!" Moment

When you realize:
> "I'm just following the grammar rules. Each rule is a function.
> If rule A contains rule B, function A calls function B.
> Recursion handles nesting automatically!"

## Bottom Line

**Don't try to understand the entire 200+ line file at once!**

1. Master the 3 helper functions (peek, accept, expect)
2. Understand ONE simple parser (number or digit)
3. Trace ONE complete example by hand
4. See the pattern repeat
5. Build up incrementally

Focus on **concepts** not memorization. In the exam, you'll have the given.c file with helpers - you just need to understand the pattern.
