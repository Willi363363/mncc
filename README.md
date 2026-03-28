# MNCC

MNCC is a small C-to-assembly transpiler prototype.

Current behavior is:

1. Read one C source file.
2. Lex it into tokens.
3. Parse top-level functions into an AST.
4. Generate NASM x86-64 assembly into `.github/a.asm`.
5. Execute `assemble.sh`, which runs NASM + LD to produce `.github/a.out`.

## What It Is (Today)

- Single-file frontend + codegen prototype.
- Targets Linux x86-64 (uses `_start` + `syscall` exit sequence).
- Produces and assembles a fixed output path (`.github/a.asm`, `.github/a.out`).
- Supports only a narrow subset of C-like syntax.

## What Is Actually Supported End-to-End

- Function definitions returning `int`
- Function parameters typed as `int` (parsed as declarations)
- Assignments with arithmetic expressions: `+`, `-`, `*`, `/`
- Function call expressions in assignments/returns
- `return;` and `return <expr>;`

Example that works with current pipeline:

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

## Important Current Limits

- CLI takes exactly one argument: `./mncc <path>`
- Output filename cannot be configured from CLI
- No control-flow parsing (`if`, `else`, `while`, `for`)
- No comparisons/logical operators
- No unary minus expression handling
- No parenthesized expression handling
- Declaration without initializer (example: `int x;`) is not accepted by parser
- Standalone call statement (example: `foo();`) is parsed but not generated
- Parser/codegen failures are printed, but the process currently may still exit with `0` due to missing error propagation in `main.c`

## Documentation

- [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md)
- [docs/GRAMMAR.md](docs/GRAMMAR.md)
- [docs/TOKENS.md](docs/TOKENS.md)
- [docs/USAGE.md](docs/USAGE.md)

## Error Codes Defined In Headers

- `0`: SUCCESS
- `84`: ERROR
- `100`: ELEX
- `101`: EPAR
- `102`: EINP
- `103`: EGEN

Note: these codes are used internally by modules, but the top-level executable currently does not always propagate parse/codegen failures to its final exit code.
