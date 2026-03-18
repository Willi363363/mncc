# MNC Architecture

## Overview

The MNC compiler is structured as a pipeline with four distinct stages:

```
Source Code → Lexer → Parser → AST → Code Generator → NASM Assembly
```

## Stage 1: Lexer (Tokenization)

The lexer scans the input character by character and produces a stream of tokens.

### Responsibilities
- Read source file character by character
- Skip whitespace and comments
- Identify keywords (`int`, `return`, etc.)
- Recognize identifiers (variable/function names)
- Parse numeric literals
- Generate token stream

### Token Structure
```c
typedef struct {
    TokenType type;
    char *text;           // Original text from source
    int value;            // Numeric value (for TOK_NUMBER)
} Token;
```

### Example
Input:
```c
int a = 3;
```

Tokens produced:
```
TOK_INT { text: "int" }
TOK_IDENT { text: "a" }
TOK_EQ { text: "=" }
TOK_NUMBER { text: "3", value: 3 }
TOK_SEMI { text: ";" }
TOK_EOF
```

## Stage 2: Parser

The parser reads tokens and builds an Abstract Syntax Tree (AST). Uses recursive descent parsing.

### Responsibilities
- Validate token sequence against grammar
- Build hierarchical AST from flat token stream
- Report syntax errors

### AST Node Types
```c
typedef enum node_type_e {
    // Instructions
    NODE_FUNCTION,      // Function definition
    NODE_BLOCK,         // Block of statements
    NODE_ASSIGN,        // Assignment: var = expr
    NODE_RETURN,        // Return statement

    // Values (Interpretable)
    NODE_CONST,         // Constant literal
    NODE_VAR,           // Variable reference
    NODE_OPERATOR,      // Binary operation: expr op expr
    NODE_CALL           // Function call: func(args)
} node_type_t;
```

### Operator Types
```c
typedef enum operator_type_e {
    OP_ADD,    // +
    OP_SUB,    // -
    OP_MUL,    // *
    OP_DIV     // /
} operator_type_t;
```

### AST Node Structure
```c
typedef struct node_s {
    node_type_t type;
    
    // For binary operations (NODE_OPERATOR, NODE_ASSIGN)
    struct node_s *left;
    struct node_s *right;
    
    // For values
    int value;              // For NODE_CONST
    char *name;             // For NODE_VAR / NODE_FUNCTION / NODE_CALL
    operator_type_t op;     // For NODE_OPERATOR
    
    // For compound structures
    array_t *childs;        // For NODE_BLOCK, NODE_FUNCTION, NODE_CALL, NODE_RETURN
} node_t;
```

### Parsing Strategy: Recursive Descent

```
parse_program()
  └─ {parse_function_def()}
       └─ parse_block()
            └─ {parse_statement()}
                 ├─ parse_assignment()
                 └─ parse_return()
```

Example: Parsing `result = a + b;`

1. Parser sees `TOK_IDENT(result)`
2. Peeks ahead, sees `TOK_EQ`
3. Calls `parse_assignment()`
4. Left side: `result` (NODE_VAR with name="result")
5. Right side: recursively parses expression
   - Sees `TOK_IDENT(a)` → NODE_VAR
   - Sees `TOK_PLUS`
   - Sees `TOK_IDENT(b)` → NODE_VAR
   - Creates `NODE_OPERATOR` with left=a, right=b, op=OP_ADD
6. Creates `NODE_ASSIGN` with left=result, right=(a+b)

## Stage 3: Semantic Analysis (Optional)

For simplicity, minimal semantic analysis:
- Track declared variables
- Validate variable uses (is it declared?)
- Type checking (minimal, all `int`)

Could be skipped if we assume input is syntactically valid.

## Stage 4: Code Generation

Recursively traverses the AST and emits NASM x86-64 assembly.

### Register Usage (Simple Stack Model)

| Register | Usage |
|----------|-------|
| `RAX` | Return value, temporary computations |
| `RBX` | Temporary for binary operations |
| `RCX`, `RDX`, etc. | Function arguments (System V ABI) |
| `RSP` | Stack pointer (managed by ABI) |
| `RBP` | Base pointer (stack frames) |

### Code Gen Strategy

For each node type, emit appropriate assembly:

**NODE_CONST**: Load value into RAX
```nasm
mov rax, 5
```

**NODE_VAR**: Load variable from memory
```nasm
mov rax, [rel varname]
```

**NODE_ASSIGN**: Compute right side and store to left
```nasm
; Evaluate right side expression
gen(right)          ; result in rax
; Store to variable
mov [rel varname], rax
```

**NODE_OPERATOR** (OP_ADD example):
```nasm
; Evaluate left
gen(left)           ; result in rax
push rax             ; save left
; Evaluate right
gen(right)          ; result in rax
pop rbx              ; restore left
add rax, rbx         ; add: rax = left + right
```

**NODE_FUNCTION**: Emit function prologue/epilogue
```nasm
function_name:
    push rbp
    mov rbp, rsp
    ; [generate function body]
    pop rbp
    ret
```

**NODE_CALL**: Set up arguments and call
```nasm
; For x86-64 System V ABI:
; - First arg in RDI
; - Second arg in RSI
; - Third arg in RDX
mov rdi, arg1_value
mov rsi, arg2_value
call function_name
; Result returned in RAX
```

**NODE_RETURN**: Return value
```nasm
gen(expr)           ; evaluate expression into rax
pop rbp
ret
```

**NODE_BLOCK**: Generate code for all statements
```nasm
# For each statement in block
gen(statement[0])
gen(statement[1])
...
```

## Full Compilation Flow

```
main(argc, argv)
  │
  ├─ lexer_create() → lexer_t with empty token array
  │
  ├─ read source file
  │
  ├─ tokenize source → fill lexer->tokens array
  │
  ├─ parser_create(lexer) → parser_t with cursor=0
  │
  ├─ parser_run(parser) → build AST
  │   └─ returns SUCCESS (0) or error code
  │
  ├─ codegen(parser->nodes) → generates NASM and writes to file
  │
  └─ exit with status code
```

## Error Handling

Simple approach:
- Lexer: report unexpected character, exit
- Parser: report unexpected token, exit
- Codegen: assume valid AST (no runtime errors)

## Memory Management

For the single-file, no-optimization version:
- Allocate once at start
- Don't worry about freeing (program exits anyway)
- Use malloc for tokens, AST nodes

Real compilers would use arena allocators or tree-walking collectors.

## Example: Compiling a Function

Input:
```c
int add(int a, int b) {
    int sum;
    sum = a + b;
    return sum;
}
```

**Lexer output:**
```
TOK_INT, TOK_IDENT(add), TOK_LPAREN, TOK_INT, TOK_IDENT(a), 
TOK_COMMA, TOK_INT, TOK_IDENT(b), TOK_RPAREN, TOK_LBRACE,
TOK_INT, TOK_IDENT(sum), TOK_SEMI,
TOK_IDENT(sum), TOK_EQ, TOK_IDENT(a), TOK_PLUS, TOK_IDENT(b), TOK_SEMI,
TOK_RETURN, TOK_IDENT(sum), TOK_SEMI,
TOK_RBRACE, TOK_EOF
```

**Parser output (AST):**
```
NODE_FUNCTION {
    name: "add",
    childs: [
        NODE_VAR(a),    // parameter a
        NODE_VAR(b),    // parameter b
        NODE_BLOCK {    // function body
            childs: [
                NODE_ASSIGN {
                    left: NODE_VAR(sum),
                    right: NODE_OPERATOR {
                        left: NODE_VAR(a),
                        right: NODE_VAR(b),
                        op: OP_ADD
                    }
                },
                NODE_RETURN {
                    childs: [NODE_VAR(sum)]
                }
            ]
        }
    ]
}
```

**Code generator output:**
```nasm
add:
    push rbp
    mov rbp, rsp
    
    ; sum = a + b
    mov rax, [rbp + 16]     ; load arg a
    push rax
    mov rax, [rbp + 24]     ; load arg b
    pop rbx
    add rax, rbx            ; a + b
    mov [rbp - 8], rax      ; store to sum
    
    ; return sum
    mov rax, [rbp - 8]
    
    pop rbp
    ret
```

## Design Decisions

1. **Single-pass pipeline**: Lexer → Parser → Codegen (no intermediate files)
2. **Full AST in memory**: Entire AST tree retained before code generation
3. **Direct code gen**: No IR (intermediate representation)
4. **Simple symbol table**: Minimal semantic analysis
5. **Basic register usage**: RAX, RBX for temporaries
6. **Stack frames**: Use RBP for function stack management
7. **Array-based node children**: Use `array_t` for flexible child count

## Roadmap for Extensions

Complexity added in order:

1. **Comparison operators**: Add support for `<`, `>`, `<=`, `>=`, `==`, `!=`
2. **Logical operators**: Add `&&`, `||`, `!`
3. **Control flow**: Add `if`, `else`, `while` statements
4. **More operators**: Add `%` (modulo), right-associative operators
5. **Comments**: Line and block comment support in lexer
6. **Variable scope**: Proper stack frame management for local variables
7. **Arrays**: Basic array support with indexing
8. **Pointers**: Pointer types and dereferencing
9. **Multiple files**: Module system and linking
10. **Optimization passes**: Dead code elimination, constant folding, etc.
