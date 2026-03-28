# MNCC Architecture

This document describes the current implementation, not an idealized compiler pipeline.

## High-Level Flow

```text
source.c
  -> lexer
  -> parser
  -> code generator
  -> .github/a.asm
  -> assemble.sh (nasm + ld)
  -> .github/a.out
```

## Entry Point

The executable logic is in `main.c`.

1. Validates CLI usage (`mncc [path]`)
2. Reads the whole file into memory
3. Runs `lexer_run`
4. Runs `parser_run`
5. If parser succeeds, runs generator and then `nasm_assemble`

The assembly path is hardcoded to `.github/a.asm`.

## Lexer

Core behavior (`src/lexer/lexer_tokenize.c`):

- Skips whitespace
- Supports line comments:
  - `// ...`
  - `# ...` (entire line ignored)
- Supports block comments: `/* ... */`
- Tokenizes identifiers, decimal numbers, operators and punctuation

Lexer outputs `token_t` values (`include/lexer/token.h`):

```c
typedef struct token_s {
    token_type_t type;
    char *value;
} token_t;
```

## Parser

The parser is recursive-descent style over a token array (`parser_t`):

- Top level: repeated function parsing until `TOK_EOF`
- Function: data type + identifier + parameter list + block
- Block: `{` + repeated instructions + `}`
- Instructions currently parsed:
  - `return` statement
  - declaration with initializer (`int x = ...;`)
  - assignment (`x = ...;`)
  - function call statement (`foo(...);`)

Important parser caveats in current code:

- `int x;` is not accepted as an instruction
- parenthesized expressions are not handled end-to-end
- unary minus is not handled
- keywords `if`, `else`, `while`, `for`, `void` are tokenized, but no parser support for control flow or void functions

## AST Model

Node types are in `include/parser/node.h`:

- Instructions: `NODE_FUNCTION`, `NODE_BLOCK`, `NODE_ASSIGN`, `NODE_DECLARATION`, `NODE_RETURN`
- Values: `NODE_CONST`, `NODE_VAR`, `NODE_OPERATOR`
- Both: `NODE_CALL`

The operator enum currently contains only `+`, `-`, `*`, `/`.

## Code Generation

Codegen writes NASM text to the output file.

Header (`src/gen/gen_header.c`) always emits:

- `section .text`
- `global _start`
- `_start` calling `main`
- Linux `exit` syscall with `main` return value

Function generation (`src/gen/gen_function.c`):

- Emits standard prologue/epilogue (`push rbp`, `mov rbp, rsp`, `leave`, `ret`)
- Stores function arguments from internal register mapping into stack slots
- Generates only block children from function node

Instruction generation supports:

- declaration (`gen_declaration`)
- assignment (`gen_assignement`)
- return (`gen_return`)
- block (`gen_block`)

Current generator limitation:

- `NODE_CALL` as a standalone instruction is not handled in `gen_instruction` and fails generation.

## Assembly and Linking Stage

After generation, `nasm_assemble` runs:

```text
sh ./assemble.sh <asm_path>
```

`assemble.sh`:

1. runs `nasm -f elf64`
2. checks that `_start` exists with `nm`
3. links using `ld -e _start`
4. writes `<basename>.out` next to the assembly file

For the default path, outputs are:

- `.github/a.asm`
- `.github/a.out`

## Error Handling Notes

- Modules print categorized errors (`ELEX`, `EPAR`, `EGEN`, `EINP`)
- The top-level command currently does not always propagate parser/generator failure to process exit code in `main.c`

In practice, you can see error messages while the executable still returns `0` in some failing cases.
