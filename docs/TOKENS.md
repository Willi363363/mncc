# MNC Token and AST Node Reference

Complete reference of token types used by the MNC lexer and AST node types used by the parser.

## Token Types (TokenType Enum)

### Data Types

| Token | Type | Meaning | Example |
|-------|------|---------|---------|
| `int` | `TOK_INT` | Integer type keyword | `int x;` |

### Keywords

| Token | Type | Meaning | Example |
|-------|------|---------|---------|
| `return` | `TOK_RETURN` | Return from function | `return 42;` |

### Identifiers & Literals

| Token | Type | Meaning | Example |
|-------|------|---------|---------|
| name | `TOK_IDENT` | Variable or function name | `foo`, `myVar` |
| number | `TOK_NUMBER` | Integer literal | `42`, `0`, `-5` |

### Operators - Assignment

| Token | Type | Meaning | Example |
|-------|------|---------|---------|
| `=` | `TOK_EQ` | Assignment | `a = 5;` |

### Operators - Arithmetic

| Token | Type | Meaning | Example |
|-------|------|---------|---------|
| `+` | `TOK_PLUS` | Addition | `a + b` |
| `-` | `TOK_MINUS` | Subtraction or negation | `a - b` or `-a` |
| `*` | `TOK_MUL` | Multiplication | `a * b` |
| `/` | `TOK_DIV` | Division | `a / b` |

### Punctuation

| Token | Type | Meaning | Example |
|-------|------|---------|---------|
| `;` | `TOK_SEMI` | Statement terminator | `int x;` |
| `,` | `TOK_COMMA` | Argument separator | `foo(a, b)` |
| `(` | `TOK_LPAREN` | Left parenthesis | `func(...)` |
| `)` | `TOK_RPAREN` | Right parenthesis | `func(...)` |
| `{` | `TOK_LBRACE` | Left brace | `{ ... }` |
| `}` | `TOK_RBRACE` | Right brace | `{ ... }` |

### Special

| Token | Type | Meaning |
|-------|------|---------|
| (end) | `TOK_EOF` | End of file |

## TokenType Enum Definition

```c
typedef enum token_type_e {
    // data types
    TOK_INT,

    // keywords
    TOK_RETURN,

    // identifiers and literals
    TOK_IDENT,
    TOK_NUMBER,

    // operators
    TOK_EQ,         // =
    TOK_PLUS,       // +
    TOK_MINUS,      // -
    TOK_MUL,        // *
    TOK_DIV,        // /

    // punctuation
    TOK_SEMI,       // ;
    TOK_LPAREN,     // (
    TOK_RPAREN,     // )
    TOK_LBRACE,     // {
    TOK_RBRACE,     // }
    TOK_COMMA,      // ,
    TOK_EOF
} token_type_t;
```

## Token Structure

```c
typedef struct token_s {
    token_type_t type;
    char *value;          // Original text from source (malloc'd)
} token_t;
```

## Lexer Rules

### Whitespace
- Spaces, tabs, newlines are skipped
- Used to separate tokens only

### Comments
- Not yet supported in current implementation

### Keywords
Reserved words that must match exactly:
- `int`, `return`

### Identifiers
- Start with letter or underscore: `[a-zA-Z_]`
- Followed by letters, digits, underscores: `[a-zA-Z_0-9]*`
- Are case-sensitive: `foo` ≠ `Foo`

### Numbers
- Decimal integers only: `[0-9]+`
- No floats, no hex, no octal
- Stored as string in token value

### Operators Supported
- `=` (assignment only)
- `+`, `-`, `*`, `/` (arithmetic)
- All single-character tokens

## Lexer Output Example

```c
// Input
int add(int a, int b) { return a + b; }

// Tokens (pseudocode)
[
    { TOK_INT, "int" },
    { TOK_IDENT, "add" },
    { TOK_LPAREN, "(" },
    { TOK_INT, "int" },
    { TOK_IDENT, "a" },
    { TOK_COMMA, "," },
    { TOK_INT, "int" },
    { TOK_IDENT, "b" },
    { TOK_RPAREN, ")" },
    { TOK_LBRACE, "{" },
    { TOK_RETURN, "return" },
    { TOK_IDENT, "a" },
    { TOK_PLUS, "+" },
    { TOK_IDENT, "b" },
    { TOK_SEMI, ";" },
    { TOK_RBRACE, "}" },
    { TOK_EOF, "" }
]
```

## Edge Cases

### Single-character Operators
All operators are single characters currently:
- `=`, `+`, `-`, `*`, `/`

### Multi-character Sequences Not Supported
- `==`, `!=` ❌
- `<=`, `>=` ❌
- `++`, `--` ❌
- `+=`, `-=` ❌

These are not yet implemented.

## Lexer Implementation Notes

1. **Character-by-character scanning**: Simple forward pass through source
2. **String storage**: Allocate and copy text for each token value
3. **Number parsing**: Store as string (conversion happens in parser/codegen)
4. **Keyword check**: When seeing identifier, check if it's a reserved keyword

---

# AST Node Types

The parser builds an Abstract Syntax Tree (AST) from the token stream. Each node represents a construct in the program.

## Node Type Categories

### Value Types (Interpretable)

These node types represent values that can be computed or used:
- `NODE_CONST` - Constant literal value
- `NODE_VAR` - Variable reference
- `NODE_OPERATOR` - Binary operation result
- `NODE_CALL` - Function call result

### Instruction Types (Statements)

These represent executable statements:
- `NODE_FUNCTION` - Function definition
- `NODE_BLOCK` - Block of statements
- `NODE_ASSIGN` - Variable assignment
- `NODE_RETURN` - Return statement

### Special Types

- `NODE_CALL` - Can be both a value type and instruction

## Node Type Details

### NODE_CONST
**Purpose**: Represents a constant integer literal

**Fields**:
- `value` - The integer constant value
- `type` = `NODE_CONST`

**Example**: `42`, `0`, `100`

**Usage**: Right-hand side of assignments, function arguments, operator operands

---

### NODE_VAR
**Purpose**: Represents a variable reference or declaration

**Fields**:
- `name` - Variable name (string)
- `type` = `NODE_VAR`

**Example**: `x`, `myVar`, `count`

**Usage**: Left-hand side of assignments, operator operands, function arguments

---

### NODE_OPERATOR
**Purpose**: Represents a binary operation

**Fields**:
- `left` - Left operand (NODE_CONST | NODE_VAR | NODE_OPERATOR | NODE_CALL)
- `right` - Right operand (NODE_CONST | NODE_VAR | NODE_OPERATOR | NODE_CALL)
- `op` - Operator type (operator_type_t enum)
- `type` = `NODE_OPERATOR`

**Operators** (operator_type_e):
- `OP_ADD` - Addition (+)
- `OP_SUB` - Subtraction (-)
- `OP_MUL` - Multiplication (*)
- `OP_DIV` - Division (/)

**Example**: `a + b`, `x * 2 + y`

**Usage**: As values in assignments, function arguments

---

### NODE_CALL
**Purpose**: Represents a function call

**Fields**:
- `name` - Function name (string)
- `childs` - Array of argument nodes (array_t of nodes)
- `type` = `NODE_CALL`

**Argument Types**: Arguments must be value types (CONST, VAR, OPERATOR, or nested CALL)

**Example**: `add(5, 10)`, `max(x, y)`

**Usage**: As values in assignments, function arguments (can be nested)

---

### NODE_ASSIGN
**Purpose**: Represents variable assignment/definition

**Fields**:
- `left` - Variable being assigned (NODE_VAR)
- `right` - Value assigned (NODE_CONST | NODE_VAR | NODE_OPERATOR | NODE_CALL)
- `type` = `NODE_ASSIGN`

**Example**: `x = 5`, `result = a + b`

**Usage**: Statement in block

---

### NODE_RETURN
**Purpose**: Represents return statement

**Fields**:
- `childs` - Array with 0 or 1 child (return value)
- Child must be value type (CONST | VAR | OPERATOR | CALL)
- `type` = `NODE_RETURN`

**Example**: `return 42`, `return x + y`, `return`

---

### NODE_BLOCK
**Purpose**: Represents a block of statements

**Fields**:
- `childs` - Array of statement nodes (array_t of nodes)
- Child statements: NODE_ASSIGN | NODE_BLOCK | NODE_RETURN
- `type` = `NODE_BLOCK`

**Example**: `{ x = 5; y = x + 10; return y; }`

**Usage**: Function body, conditional/loop bodies

---

### NODE_FUNCTION
**Purpose**: Represents a function definition

**Fields**:
- `name` - Function name (string)
- `childs` - Array of parameter names (NODE_VAR nodes)
- Function body is typically a single NODE_BLOCK child
- `type` = `NODE_FUNCTION`

**Example**: `int add(int a, int b) { return a + b; }`

---

## Complete Node Structure

```c
typedef enum operator_type_e {
    OP_ADD,    // +
    OP_SUB,    // -
    OP_MUL,    // *
    OP_DIV     // /
} operator_type_t;

typedef enum node_type_e {
    // Instructions
    NODE_FUNCTION,
    NODE_BLOCK,
    NODE_ASSIGN,
    NODE_RETURN,

    // Values
    NODE_CONST,
    NODE_VAR,
    NODE_OPERATOR,

    // Both
    NODE_CALL
} node_type_t;

typedef struct node_s {
    node_type_t type;

    // For binary operations (NODE_OPERATOR, NODE_ASSIGN)
    struct node_s *left;
    struct node_s *right;

    char *name;         // For NODE_VAR / NODE_FUNCTION / NODE_CALL
    int value;          // For NODE_CONST
    operator_type_t op; // For NODE_OPERATOR

    array_t *childs;    // For NODE_BLOCK, NODE_FUNCTION, NODE_CALL, NODE_RETURN
} node_t;
```

## Tree Structure Examples

### Simple Assignment In Function

```c
int main() {
    int x;
    x = 42;
    return x;
}
```

AST structure:
```
NODE_FUNCTION (name: "main")
└── childs[0]: NODE_BLOCK
    ├── childs[0]: NODE_ASSIGN
    │   ├── left: NODE_VAR (name: "x")
    │   └── right: NODE_CONST (value: 42)
    └── childs[1]: NODE_RETURN
        └── childs[0]: NODE_VAR (name: "x")
```

### Binary Operation

```c
int add(int a, int b) {
    return a + b;
}
```

AST structure:
```
NODE_FUNCTION (name: "add")
├── childs[0]: NODE_VAR (name: "a")
├── childs[1]: NODE_VAR (name: "b")
└── NODE_BLOCK
    └── childs[0]: NODE_RETURN
        └── childs[0]: NODE_OPERATOR (op: OP_ADD)
            ├── left: NODE_VAR (name: "a")
            └── right: NODE_VAR (name: "b")
```

### Function Call with Arguments

```c
int result = multiply(add(2, 3), 4);
```

Value type:
```
NODE_OPERATOR (op: OP_MUL)
├── left: NODE_CALL (name: "add")
│   ├── childs[0]: NODE_CONST (value: 2)
│   └── childs[1]: NODE_CONST (value: 3)
└── right: NODE_CONST (value: 4)
```

## Type Hierarchy

```
All Nodes
├── Instructions (for NODE_BLOCK)
│   ├── NODE_BLOCK
│   ├── NODE_ASSIGN
│   └── NODE_RETURN
│
└── Value Types (interpretable)
    ├── NODE_CONST
    ├── NODE_VAR
    ├── NODE_OPERATOR
    └── NODE_CALL (also usable in statements)
```

## Constraints

1. **NODE_OPERATOR**: Both operands must be value types
2. **NODE_ASSIGN**: 
   - Left must be NODE_VAR
   - Right must be value type
3. **NODE_RETURN**: Child (if exists) must be value type
4. **NODE_BLOCK**: Children must be instruction types
5. **NODE_CALL**: Arguments in `childs` must be value types
6. **NODE_FUNCTION**: Parameters are NODE_VAR nodes, body is typically NODE_BLOCK
