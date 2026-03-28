# MNCC Token And AST Reference

This document matches the current enums and behavior in source.

## Token Types

Defined in `include/lexer/token.h`.

### Data / Literals

- `TOK_INT`
- `TOK_NUMBER`

### Keywords

- `TOK_RETURN`
- `TOK_IF`
- `TOK_ELSE`
- `TOK_WHILE`
- `TOK_FOR`
- `TOK_VOID`

### Identifiers

- `TOK_IDENT`

### Operators

- `TOK_EQ` (`=`)
- `TOK_PLUS` (`+`)
- `TOK_MINUS` (`-`)
- `TOK_MUL` (`*`)
- `TOK_DIV` (`/`)

### Punctuation

- `TOK_SEMI` (`;`)
- `TOK_LPAREN` (`(`)
- `TOK_RPAREN` (`)`)
- `TOK_LBRACE` (`{`)
- `TOK_RBRACE` (`}`)
- `TOK_COMMA` (`,`) 
- `TOK_EOF`

## Lexer Notes

Implemented behavior (`src/lexer/lexer_tokenize.c`):

- Whitespace skipped
- Line comments supported:
  - `// ...`
  - `# ...`
- Block comments supported: `/* ... */`
- Recognized identifiers: `[a-zA-Z_][a-zA-Z0-9_]*`
- Numbers: decimal digits only

Tokenized but currently not parsed for full language features:

- `if`, `else`, `while`, `for`, `void`

## AST Enums

Defined in `include/parser/node.h`.

### Data Type Enum

- `DATA_INT`
- `DATA_POINTER`
- `DATA_INVALID`

### Operator Enum

- `OP_ADD`
- `OP_SUB`
- `OP_MUL`
- `OP_DIV`
- `OP_INVALID`

### Node Type Enum

- `NODE_FUNCTION`
- `NODE_BLOCK`
- `NODE_ASSIGN`
- `NODE_DECLARATION`
- `NODE_RETURN`
- `NODE_CONST`
- `NODE_VAR`
- `NODE_OPERATOR`
- `NODE_CALL`

## Node Structure

```c
typedef struct node_s {
    node_type_t type;
    struct node_s *left;
    struct node_s *right;

    data_type_t data_type;
    char *name;
    int value;
    operator_type_t op;

    array_t *childs;
} node_t;
```

## Practical Node Usage In Current Parser

- `NODE_FUNCTION`
  - `name`: function name
  - `data_type`: return type (currently parsed as int/pointer-int)
  - `childs`: parameter declarations and one block node
- `NODE_BLOCK`
  - `childs`: instructions
- `NODE_DECLARATION`
  - with initializer: wraps assignment-like left/right
  - without initializer: parser currently does not accept this statement form
- `NODE_ASSIGN`
  - `left`: variable node
  - `right`: expression node
- `NODE_RETURN`
  - `childs`: zero or one expression node
- `NODE_CALL`
  - `name`: function name
  - `childs`: argument expressions

## Parser/Generator Mismatches To Keep In Mind

- Parser can produce `NODE_CALL` as statement (`foo();`), but codegen instruction dispatch does not support it.
- Some tokens exist in lexer but have no parser integration (`TOK_IF`, `TOK_ELSE`, `TOK_WHILE`, `TOK_FOR`, `TOK_VOID`).
