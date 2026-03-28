# MNCC Grammar

This grammar describes what the current parser accepts, including known quirks.

## Notation

```text
[x]        optional
{x}        zero or more repetitions
x | y      choice
```

## Top-Level

```text
program       -> { function }

function      -> data_type IDENT "(" [ params ] ")" block
params        -> param { "," param }
param         -> data_type IDENT | data_type IDENT "=" expression
data_type     -> "int" { "*" }
```

Notes:

- `void` is tokenized by lexer but not accepted by `parse_data_type`.
- pointer stars after `int` are parsed as type metadata only.

## Blocks And Instructions

```text
block         -> "{" { instruction } "}"

instruction   -> return_stmt ";"
              | declaration_with_init ";"
              | assignment ";"
              | call ";"

declaration_with_init
              -> data_type IDENT "=" expression

assignment    -> IDENT "=" expression

return_stmt   -> "return" [ expression ]
```

Important: plain declaration without initializer (`int x;`) is currently rejected.

## Expressions

```text
expression    -> value
              | operator_expression

value         -> NUMBER
              | IDENT
              | call

call          -> IDENT "(" [ arguments ] ")"
arguments     -> expression { "," expression }

operator_expression
              -> expression ("+" | "-" | "*" | "/") expression
```

## Operator Handling

Supported operator tokens:

- `+`
- `-`
- `*`
- `/`

The parser tries operators in this internal order:

1. `+`
2. `-`
3. `*`
4. `/`

This gives right-recursive trees for many expressions (as seen in tests), but there is no full precedence/associativity engine and no parenthesized-expression implementation.

## Explicitly Not Supported

- control flow statements (`if`, `else`, `while`, `for`)
- comparisons (`==`, `!=`, `<`, `<=`, `>`, `>=`)
- logical operators (`&&`, `||`, `!`)
- modulo (`%`)
- unary minus (`-x`)
- parenthesized expressions (`(a + b)`)

## Parse vs Generate Mismatch

`call;` as a standalone instruction is parsed, but generator instruction dispatch does not implement `NODE_CALL`, so generation fails for this form.
