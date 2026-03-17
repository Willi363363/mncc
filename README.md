# MNC - Mini C Compiler

A minimal C compiler written in C that compiles a single C file to NASM x86-64 assembly.

## Overview

MNC is a barebones compiler that follows the classic compiler architecture without optimizations, multi-file support, or advanced features. It reads a C source file and outputs NASM-compatible x86-64 assembly.

### Key Features
- **Single file compilation**: Compiles one C file at a time
- **No optimizations**: Straightforward, readable assembly output
- **Simple subset of C**: Variables, functions, basic operators, control flow
- **Direct NASM output**: Ready to assemble with `nasm -f elf64`

## Quick Start

```bash
# Build the compiler
make

# Compile a C file to NASM
./mncc example.c

# Assemble and link
nasm -f elf64 example.asm -o example.o
ld example.o -o example
```

## Compiler Stages

MNC follows the standard compiler pipeline:

1. **Lexing**: Tokenize C source code
2. **Parsing**: Build Abstract Syntax Tree (AST)
3. **Semantic Analysis**: Type checking and variable validation
4. **Code Generation**: Traverse AST and emit NASM instructions

## Supported Constructs

### Data Types
- `int` - 64-bit signed integers only

### Statements
- Variable declarations: `int x;`
- Assignments: `a = 5 + 3;`
- Function declarations and calls
- Return statements
- Block statements with `{}`

### Operators
- **Arithmetic**: `+`, `-`, `*`, `/`
- **Assignment**: `=`
- **Comparison**: `<`, `>`, `<=`, `>=`, `==`, `!=`

### Example Input

```c
int add(int a, int b) {
    int result;
    result = a + b;
    return result;
}

int main() {
    int x;
    int y;
    x = 10;
    y = 20;
    int z;
    z = add(x, y);
    return z;
}
```

## Documentation Structure

- **README.md** - This file; quick overview
- **ARCHITECTURE.md** - Detailed compiler structure and design
- **TOKENS.md** - Token types and lexer reference
- **GRAMMAR.md** - BNF-like grammar of supported C subset
- **USAGE.md** - Command-line usage and examples

## Project Structure

```
mncc/
├── docs/              # Documentation
│   ├── ARCHITECTURE.md
│   ├── TOKENS.md
│   ├── GRAMMAR.md
│   └── USAGE.md
├── include/           # Header files
│   └── mncc.h         # Main compiler structures
├── src/               # Source code
│   └── main.c         # Entry point
├── tests/             # Test suite
│   └── tests.c
├── Makefile
├── README.md
└── .git/
```

## Building

```bash
make                  # Build mncc binary
make clean            # Remove object files
make tests            # Run test suite (with Criterion)
```

## Limitations

- No preprocessor (`#include`, `#define`)
- No pointers or arrays
- No struct/union types
- No standard library calls (only assembly output)
- No inter-file linking
- Single `int` type only
- No function prototypes (declarations must precede use)
- Variables are global or function-local only

## Next Steps

1. Read [ARCHITECTURE.md](docs/ARCHITECTURE.md) to understand the compiler design
2. Check [TOKENS.md](docs/TOKENS.md) for the complete token reference
3. Review [GRAMMAR.md](docs/GRAMMAR.md) for supported language constructs
4. See [USAGE.md](docs/USAGE.md) for practical examples

## Implementation Notes

- All code fits in a single C file when possible
- No function static or file-scoped declarations
- Stack-based register allocation (RAX, RBX for temporary values)
- Direct AST traversal for code generation
