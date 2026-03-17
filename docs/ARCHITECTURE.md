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
typedef enum {
    NODE_NUMBER,      // Literal integer
    NODE_VAR,         // Variable reference
    NODE_ASSIGN,      // Assignment: a = expr
    NODE_OP_ADD,      // Binary: expr + expr
    NODE_OP_SUB,      // Binary: expr - expr
    NODE_OP_MUL,      // Binary: expr * expr
    NODE_OP_DIV,      // Binary: expr / expr
    NODE_OP_CMP,      // Comparison: <, >, <=, >=, ==, !=
    NODE_FUNC_CALL,   // Function call: func(args)
    NODE_FUNC_DEF,    // Function definition
    NODE_BLOCK,       // Block: { statements }
    NODE_RETURN,      // Return statement
    NODE_DECL,        // Variable declaration: int x;
} NodeType;
```

### AST Node Structure
```c
typedef struct Node {
    NodeType type;
    
    // For binary operations
    struct Node *left;
    struct Node *right;
    
    // For values
    int value;              // Integer literal value
    char *name;             // Variable/function name
    
    // For function def / calls
    struct Node **args;     // Argument list
    int arg_count;
    struct Node *body;      // Function body (for NODE_FUNC_DEF)
    
    // For blocks
    struct Node **statements;
    int stmt_count;
} Node;
```

### Parsing Strategy: Recursive Descent

```
parse_program()
  └─ parse_function_def()
       └─ parse_block()
            └─ parse_statement()
                 ├─ parse_return()
                 ├─ parse_declaration()
                 └─ parse_assignment()
```

Example: Parsing `a = 3 + 2;`

1. Parser sees `TOK_IDENT(a)`
2. Peeks ahead, sees `TOK_EQ`
3. Calls `parse_assignment()`
4. Left side: `a` (NODE_VAR)
5. Right side: recursively parses expression
   - Sees `TOK_NUMBER(3)` → NODE_NUMBER
   - Sees `TOK_PLUS`
   - Sees `TOK_NUMBER(2)` → NODE_NUMBER
   - Creates `NODE_OP_ADD` with left=3, right=2
6. Creates `NODE_ASSIGN` with left=`a`, right=`(3+2)`

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
| `RSP` | Stack pointer (managed by ABI) |

### Code Gen Strategy

For each node type, emit appropriate assembly:

**NODE_NUMBER**: Load value into RAX
```nasm
mov rax, 5
```

**NODE_VAR**: Load variable from memory
```nasm
mov rax, [rel varname]
```

**NODE_ASSIGN**: Store to variable
```nasm
; compute right side into rax
mov [rel varname], rax
```

**NODE_OP_ADD**:
```nasm
; left value
gen(left)          ; result in rax
push rax            ; save it
; right value
gen(right)         ; result in rax
pop rbx             ; restore left
add rax, rbx        ; add them
```

**NODE_FUNC_DEF**: Emit function prologue/epilogue
```nasm
function_name:
    push rbp
    mov rbp, rsp
    ; body
    pop rbp
    ret
```

**NODE_FUNC_CALL**: Set up arguments, call
```nasm
; For x86-64 System V ABI:
; - First arg in RDI
; - Second arg in RSI
; - Third arg in RDX
; Result in RAX
mov rdi, arg1_value
mov rsi, arg2_value
call function_name
```

## Full Compilation Flow

```
main(argv[1])
  │
  ├─ read_file(argv[1]) → char*
  │
  ├─ lexer(char*) → Token[]
  │
  ├─ parser(Token[]) → Node* (AST)
  │
  ├─ codegen(Node*) → prints to stdout or file
  │   (writes assembly.asm)
  │
  └─ exit(0)
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
NODE_FUNC_DEF {
    name: "add",
    args: [NODE_VAR(a), NODE_VAR(b)],
    body: NODE_BLOCK {
        statements: [
            NODE_DECL(sum),
            NODE_ASSIGN {
                left: NODE_VAR(sum),
                right: NODE_OP_ADD {
                    left: NODE_VAR(a),
                    right: NODE_VAR(b)
                }
            },
            NODE_RETURN {
                expr: NODE_VAR(sum)
            }
        ]
    }
}
```

**Code generator output:**
```nasm
add:
    push rbp
    mov rbp, rsp
    
    ; sum = a + b
    mov rax, [rbp + 16]     ; load a
    push rax
    mov rax, [rbp + 24]     ; load b
    pop rbx
    add rax, rbx            ; a + b
    mov [rbp - 8], rax      ; store to sum
    
    ; return sum
    mov rax, [rbp - 8]
    
    pop rbp
    ret
```

## Design Decisions

1. **Single-pass**: Lexer → Parser → Codegen (no intermediate files)
2. **AST preservation**: Entire AST in memory (simple, not scalable)
3. **Direct code gen**: No IR (intermediate representation)
4. **Global pass**: All variables global scope, or function-local
5. **No register allocation**: Just RAX, RBX for temps
6. **Stack frame**: Use RBP for function locals

## Future Extensions

If adding complexity in order:

1. Add local variable scope (stack frames)
2. Add arrays and indexing
3. Add control flow (if/else, loops)
4. Add function prototypes
5. Add pointers
6. Add structs
7. Add multiple files and linking
8. Add optimization passes
