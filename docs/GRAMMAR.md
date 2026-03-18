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

statement → assignment ";"
          | return_stmt

assignment → IDENT "=" expression

return_stmt → "return" [expression] ";"
```

### Expressions

```
expression → additive_expr

additive_expr → multiplicative_expr {("+" | "-") multiplicative_expr}

multiplicative_expr → unary_expr {("*" | "/" | "%") unary_expr}

unary_expr → "-" unary_expr
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
| 1 | `+`, `-` (binary) | left |
| 2 | `*`, `/`, `%` | left |
| 3 | `-` (unary) | right |

## Example Programs

### Simple Assignment In Function

```c
int add(int a, int b) {
    int result;
    result = a + b;
    return result;
}
```

Parses as:
```
program:
  function_def:
    name: "add"
    params: [a, b]
    block:
      assign: result = (a + b)
      return: result
```

### Function Call

```c
int main() {
    int sum;
    sum = add(10, 32);
    return sum;
}
```

Parses as:
```
program:
  function_def:
    name: "main"
    params: []
    block:
      assign: sum = add(10, 32)
      return: sum
```

## Constraints & Limitations

### No Support For

- **Pointers** (`*`, `&`, `->`)
- **Arrays** (`[]`)
- **Structs/Unions** (`.`, `->`)
- **Typedef**, **Enum**
- **Floating point** (double, float)
- **Strings** (char arrays)
- **Function pointers**
- **Preprocessor** (`#include`, `#define`)
- **Conditional statements** (`if`, `else`)
- **Loops** (`while`, `for`)
- **Comparison operators** (`<`, `>`, `<=`, `>=`, `==`, `!=`)
- **Logical operators** (`&&`, `||`, `!`)

### Scope Rules

1. All function names must be unique
2. Function parameters and local variables are function-scoped
3. No nested function scopes
4. All variables are function-local or global

### Type Rules

- All types are `int` (64-bit signed integer)
- No type coercion or casting
- All operations preserve `int` type
- Function must return `int`

### Other Rules

- Variable must be declared before use
- `main()` function should exist (entry point)
- All statements must end with `;`
- Parameters must be declared as `int IDENT`

## Valid Program Structure

```c
int helper(int x) {
    int result;
    result = x * 2;
    return result;
}

int main() {
    int value;
    value = helper(5);
    return value;
}
```

## Invalid Programs (Rejected by Parser)

```c
// ❌ Missing semicolon
int main() {
    int x = 5
}

// ❌ If statements not supported
int max(int a, int b) {
    if (a > b) return a;
    return b;
}

// ❌ Unsupported: pointers
int *ptr;

// ❌ Unsupported: array
int arr[10];

// ❌ Unsupported: comparison operators
int is_positive(int x) {
    return x > 0;
}
```

## Parser Error Recovery

Current parser: **no error recovery**
- First syntax error → parser exits immediately
- Reports error message with error code
- Doesn't attempt to continue parsing

## Expression Examples

Valid expressions (all evaluate to `int`):

```
5                    // constant
x                    // variable
x + 5                // addition
x + y * 2            // precedence: y*2 first, then +
(x + y) * 2          // parentheses override
-x                   // unary minus
func(1, 2, 3)        // function call
func(x + 1, y)       // nested expressions in args
```
