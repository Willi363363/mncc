# MNCC Usage Guide

This guide follows current runtime behavior from the repository code.

## Command

```bash
./mncc <path_to_c_file>
```

- Exactly one source argument is accepted.
- `-h` prints usage text.
- There is no output filename argument in current CLI.

## Runtime Outputs

When compilation/parsing/generation succeeds, MNCC writes:

- Assembly: `.github/a.asm`
- Executable: `.github/a.out`

The executable is produced automatically via `assemble.sh` (MNCC invokes NASM and LD itself).

## Requirements

Tools expected at runtime:

- `nasm`
- `ld`
- `nm` (used by `assemble.sh` to validate `_start`)

## Minimal Working Example

Create `sample.c`:

```c
int add(int a, int b)
{
    return a + b;
}

int main()
{
    return add(15, 8);
}
```

Run MNCC:

```bash
./mncc sample.c
```

Run produced binary:

```bash
./.github/a.out
echo $?
```

For this sample, the exit code is `23`.

## Inspect Generated Assembly

```bash
./mncc sample.c
cat .github/a.asm
```

Header is always generated as:

```nasm
section .text
                global _start

_start:
                call main
                mov rdi, rax
                mov rax, 60
                syscall
```

## Supported Source Patterns (Current)

- `int` functions
- function parameters
- assignments with expressions using `+ - * /`
- return statements
- function calls used as expressions

## Known Non-Working Patterns

- `int x;` declaration without initializer
- unary minus (`-x`)
- parenthesized expressions (`(a + b)`)
- control flow (`if`, `else`, `while`, `for`)
- standalone call instruction (`foo();`) at codegen stage

## Comments And Preprocessor-Like Lines

Lexer currently skips:

- `// line comments`
- `/* block comments */`
- lines starting with `#` (treated like line comments)

This means `#include ...` is ignored by the lexer rather than implemented as a real preprocessor.

## About Exit Codes

Error messages are printed for lexer/parser/generator failures, but the top-level command currently may still return `0` for some parse/generation failures.

If you need reliability today, validate both:

1. stderr output for errors
2. existence and freshness of `.github/a.out`
