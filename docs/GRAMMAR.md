# MNC Grammar

Formal grammar for the minimal C subset supported by MNC.

## BNF-like Notation

```
[item]           - optional
{item}           - zero or more repetitions
item1 | item2    - choice
"string"         - literal token
IDENT, NUMBER    - token types
```

## Grammar Rules

### Top Level

```
program → {function_def}

function_def → "int" IDENT "(" [param_list] ")" "{" block "}"

param_list → "int" IDENT {"," "int" IDENT}
```

### Blocks & Statements

```
block → {statement}

statement → declaration
          | assignment
          | return_stmt
          | if_stmt
          | while_stmt
          | ";" (empty statement)

declaration → "int" IDENT ";"

assignment → IDENT "=" expression ";"

return_stmt → "return" [expression] ";"

if_stmt → "if" "(" expression ")" "{" block "}" ["else" "{" block "}"]

while_stmt → "while" "(" expression ")" "{" block "}"
```

### Expressions

```
expression → assignment_expr

assignment_expr → logical_or_expr

logical_or_expr → logical_and_expr {("||") logical_and_expr}

logical_and_expr → equality_expr {("&&") equality_expr}

equality_expr → relational_expr {("==" | "!=") relational_expr}

relational_expr → additive_expr {("<" | ">" | "<=" | ">=") additive_expr}

additive_expr → multiplicative_expr {("+" | "-") multiplicative_expr}

multiplicative_expr → unary_expr {("*" | "/" | "%") unary_expr}

unary_expr → ("!" | "-") unary_expr
           | postfix_expr

postfix_expr → primary_expr ["(" [arg_list] ")"]

primary_expr → IDENT
             | NUMBER
             | "(" expression ")"

arg_list → expression {"," expression}
```

## Operator Precedence (lowest to highest)

| Precedence | Operator | Associativity |
|------------|----------|---------------|
| 1 | `\|\|` (logical OR) | left |
| 2 | `&&` (logical AND) | left |
| 3 | `==`, `!=` | left |
| 4 | `<`, `>`, `<=`, `>=` | left |
| 5 | `+`, `-` | left |
| 6 | `*`, `/`, `%` | left |
| 7 | `!`, `-` (unary) | right |

## Example Programs

### Simple Assignment

```c
int main() {
    int x;
    x = 5;
    return x;
}
```

Parses as:
```
program:
  function_def:
    name: "main"
    params: []
    block:
      declaration: "x"
      assignment: x = 5
      return: x
```

### Function with Parameters

```c
int add(int a, int b) {
    return a + b;
}
```

Parses as:
```
program:
  function_def:
    name: "add"
    params: ["a", "b"]
    block:
      return: (a + b)
```

### Conditional

```c
int max(int x, int y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}
```

Parses as:
```
program:
  function_def:
    name: "max"
    params: ["x", "y"]
    block:
      if_stmt:
        condition: (x > y)
        then_block: return x
        else_block: return y
```

### Loop

```c
int sum_to(int n) {
    int sum;
    int i;
    sum = 0;
    i = 0;
    while (i < n) {
        sum = sum + i;
        i = i + 1;
    }
    return sum;
}
```

## Constraints & Limitations

### No Support For

- **Pointers** (`*`, `&`, `->`)
- **Arrays** (`[]`)
- **Structs/Unions** (`.`, `->`)
- **Typedef** 
- **Enum**
- **Floating point** (double, float)
- **Strings** (char arrays)
- **Function pointers**
- **Multiple return types** (only `int`)
- **Preprocessor** (`#include`, `#define`)

### Scope Rules

1. **Global scope**: All functions, all variables without function
2. **Function scope**: Function parameters and local variables
3. **No nested function scopes**: Can't declare nested functions
4. **No block scope**: Variables declared anywhere in function are function-scoped

### Type Rules

- All types are `int` (64-bit signed integer)
- No type coercion or casting
- All operations preserve `int` type
- Function must return `int`

### Other Rules

- Function names must be unique
- Variable names must be unique (within scope)
- Variable must be declared before use
- `main()` function should exist (entry point)
- All statements must end with `;`

## Valid Program Structure

```c
int func1(int a, int b) {
    int local1;
    int local2;
    local1 = a + b;
    local2 = a - b;
    return local1;
}

int func2(int x) {
    return func1(x, 10);
}

int main() {
    int result;
    result = func2(5);
    return result;
}
```

## Invalid Programs (Rejected by Parser)

```c
// ❌ Missing semicolon
int x = 5

// ❌ Undeclared variable
func(undeclared);

// ❌ No return type specified
foo(int a) { }

// ❌ Unsupported: pointers
int *ptr;

// ❌ Unsupported: array
int arr[10];

// ❌ Missing braces
int func() return 5;
```

## Parser Error Recovery

Current parser: **no error recovery**
- First syntax error → parser exits immediately
- Reports error message with context
- Doesn't attempt to continue parsing

## Expression Examples

Valid expressions (all evaluate to `int`):

```
5                    // number
x                    // variable
x + 5                // addition
x + y * 2            // precedence: y*2 first, then +
(x + y) * 2          // parentheses override
x < 10               // comparison (0 false, 1 true)
x == 5 && y > 0      // logical AND (result: 0 or 1)
!x                   // logical NOT
-x                   // unary minus
func(1, 2, 3)        // function call
```
