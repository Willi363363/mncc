# MNC - Mini C Compiler

A minimal C compiler written in C that compiles a single C file to NASM x86-64 assembly.

## Overview

MNC is a barebones compiler that follows the classic compiler architecture without optimizations or multi-file support. It reads a C source file, tokenizes it, builds an abstract syntax tree, and outputs NASM-compatible x86-64 assembly.

### Key Features
- **Single file compilation**: Compiles one C file at a time
- **No optimizations**: Straightforward, readable assembly output
- **Simple subset of C**: Variables, functions, basic operators
- **Direct NASM output**: Ready to assemble with `nasm -f elf64`

## Quick Start

```bash
# Build the compiler
make

# Compile a C file to NASM
./mncc example.c

# Assemble and link
nasm -f elf64 output.asm -o output.o
ld output.o -o example
./example
echo $?  # Check exit code
```

## Compiler Pipeline

MNC follows the standard compiler stages:

1. **Lexing**: Tokenize C source code into token stream
2. **Parsing**: Build Abstract Syntax Tree (AST) using recursive descent
3. **Code Generation**: Traverse AST and emit NASM instructions

## Supported Constructs

### Data Types
- `int` - 64-bit signed integers only

### Language Features
- Function definitions with parameters and return values
- Variable declarations and assignments
- Arithmetic expressions: `+`, `-`, `*`, `/`
- Unary minus: `-x`
- Function calls with arguments
- Return statements

### Example Program

```c
int add(int a, int b) {
    int result;
    result = a + b;
    return result;
}

int main() {
    int x;
    x = add(10, 32);
    return x;
}
```

## Documentation Structure

- **[README.md](README.md)** - This file; quick overview
- **[ARCHITECTURE.md](ARCHITECTURE.md)** - Detailed compiler design and pipeline
- **[TOKENS.md](TOKENS.md)** - Token types and AST node reference
- **[GRAMMAR.md](GRAMMAR.md)** - BNF-like grammar of supported C subset
- **[USAGE.md](USAGE.md)** - Practical examples and workflows

## Project Structure

```
mncc/
├── docs/              # Documentation
│   ├── README.md
│   ├── ARCHITECTURE.md
│   ├── TOKENS.md
│   ├── GRAMMAR.md
│   └── USAGE.md
├── include/           # Header files
│   ├── main.h
│   ├── lexer/
│   │   ├── lexer.h
│   │   └── token.h
│   ├── parser/
│   │   ├── parser.h
│   │   └── node.h
│   └── utils/
├── src/               # Source code
│   ├── main.c
│   ├── lexer/
│   ├── parser/
│   ├── codegen/
│   └── utils/
├── tests/             # Test suite
├── Makefile
└── .git/
```

## Building

```bash
make                  # Build mncc binary
make clean            # Remove object files
make fclean           # Clean everything
make re               # Rebuild from scratch
make tests            # Run test suite
```

## Limitations

- **No control flow**: `if`, `else`, `while` not supported
- **No comparisons**: `<`, `>`, `<=`, `>=`, `==`, `!=` not supported
- **No logical operators**: `&&`, `||`, `!` not supported  
- **No preprocessor**: `#include`, `#define`
- **No pointers or arrays**: Limited to basic types
- **No struct/union types**
- **No standard library**: No I/O functions

## Next Steps

1. Read [ARCHITECTURE.md](docs/ARCHITECTURE.md) for compiler design details
2. Check [TOKENS.md](docs/TOKENS.md) for complete token and AST node reference
3. Review [GRAMMAR.md](docs/GRAMMAR.md) for language grammar
4. See [USAGE.md](docs/USAGE.md) for practical compilation examples

## Error Codes

- `0` - SUCCESS
- `84` - GENERAL ERROR
- `100` (ELEX) - Lexer error
- `101` (EPAR) - Parser error
- `102` (EINP) - Input error
- `103` (EGEN) - Code generation error
