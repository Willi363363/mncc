# MNC Token Reference

Complete reference of all token types used by the MNC lexer.

## Token Types (TokenType Enum)

### Keywords

| Token | Type | Meaning | Example |
|-------|------|---------|---------|
| `int` | `TOK_INT` | Integer type keyword | `int x;` |
| `return` | `TOK_RETURN` | Return from function | `return 42;` |
| `if` | `TOK_IF` | Conditional statement | `if (x > 0) { ... }` |
| `else` | `TOK_ELSE` | Else branch | `else { ... }` |
| `while` | `TOK_WHILE` | While loop | `while (x < 10) { ... }` |

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
| `%` | `TOK_MOD` | Modulo | `a % b` |

### Operators - Comparison

| Token | Type | Meaning | Example |
|-------|------|---------|---------|
| `<` | `TOK_LT` | Less than | `a < b` |
| `>` | `TOK_GT` | Greater than | `a > b` |
| `<=` | `TOK_LE` | Less than or equal | `a <= b` |
| `>=` | `TOK_GE` | Greater than or equal | `a >= b` |
| `==` | `TOK_EQEQ` | Equality | `a == b` |
| `!=` | `TOK_NE` | Not equal | `a != b` |

### Operators - Logical

| Token | Type | Meaning | Example |
|-------|------|---------|---------|
| `&&` | `TOK_AND` | Logical AND | `a && b` |
| `\|\|` | `TOK_OR` | Logical OR | `a \|\| b` |
| `!` | `TOK_NOT` | Logical NOT | `!a` |

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
typedef enum {
    // Keywords
    TOK_INT,
    TOK_RETURN,
    TOK_IF,
    TOK_ELSE,
    TOK_WHILE,
    
    // Identifiers and literals
    TOK_IDENT,
    TOK_NUMBER,
    
    // Assignment
    TOK_EQ,
    
    // Arithmetic operators
    TOK_PLUS,
    TOK_MINUS,
    TOK_MUL,
    TOK_DIV,
    TOK_MOD,
    
    // Comparison operators
    TOK_LT,
    TOK_GT,
    TOK_LE,
    TOK_GE,
    TOK_EQEQ,
    TOK_NE,
    
    // Logical operators
    TOK_AND,
    TOK_OR,
    TOK_NOT,
    
    // Punctuation
    TOK_SEMI,
    TOK_COMMA,
    TOK_LPAREN,
    TOK_RPAREN,
    TOK_LBRACE,
    TOK_RBRACE,
    
    // End of file
    TOK_EOF
} TokenType;
```

## Token Structure

```c
typedef struct {
    TokenType type;
    char *text;           // Original text from source (malloc'd)
    int value;            // For numeric tokens
    int line;             // Line number in source (optional)
    int column;           // Column in line (optional)
} Token;
```

## Lexer Rules

### Whitespace
- Spaces, tabs, newlines are skipped
- Used to separate tokens only

### Comments
- `// single line comment` (skip to end of line)
- `/* block comment */` (skip until `*/`)

### Keywords
Reserved words that must match exactly:
- `int`, `return`, `if`, `else`, `while`

### Identifiers
- Start with letter or underscore: `[a-zA-Z_]`
- Followed by letters, digits, underscores: `[a-zA-Z_0-9]*`
- Are case-sensitive: `foo` ≠ `Foo`

### Numbers
- Decimal integers only: `[0-9]+`
- No floats, no hex, no octal
- Converted to `int` value in token

### Multi-character operators
- `==` parsed as one token (not two `=`)
- `!=` parsed as one token (not `!` followed by `=`)
- `<=`, `>=` similar

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

### Ambiguities Resolved

- `-` vs `--`: Just `-` (no decrement operator)
- `=` vs `==`: Look-ahead determines which
- `/` vs `/*`: Look-ahead distinguishes division from comment start

### No Multi-character operators (list)
- `++`, `--` ❌
- `+=`, `-=` ❌
- `->`, `.` ❌

These aren't supported and will cause lexer errors.

## Lexer Implementation Notes

1. **Look-ahead**: Sometimes need to peek 1-2 chars ahead
2. **String storage**: Allocate and copy text for each token
3. **Number conversion**: Parse string digits to `int` value
4. **Keyword check**: When seeing identifier, check if it's a keyword
