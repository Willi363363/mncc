/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** mncc.h - Main header for the MNC compiler
*/

#ifndef MNCC_H
    #define MNCC_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    typedef enum {
        TOK_INT, TOK_RETURN, TOK_IF, TOK_ELSE, TOK_WHILE,
        TOK_IDENT, TOK_NUMBER,
        TOK_EQ, TOK_PLUS, TOK_MINUS, TOK_MUL, TOK_DIV, TOK_MOD,
        TOK_LT, TOK_GT, TOK_LE, TOK_GE, TOK_EQEQ, TOK_NE,
        TOK_AND, TOK_OR, TOK_NOT,
        TOK_SEMI, TOK_COMMA, TOK_LPAREN, TOK_RPAREN,
        TOK_LBRACE, TOK_RBRACE,
        TOK_EOF
    } token_type_t;

    typedef struct {
        token_type_t type;
        char *text;
        int value;
        int line;
    } token_t;

    typedef struct {
        char *src;
        int pos;
        int line;
        token_t *tokens;
        int count;
        int capacity;
    } lexer_t;

    typedef enum {
        NODE_NUMBER, NODE_VAR,
        NODE_ASSIGN, NODE_DECL, NODE_RETURN,
        NODE_OP_ADD, NODE_OP_SUB, NODE_OP_MUL,
        NODE_OP_DIV, NODE_OP_MOD,
        NODE_OP_CMP, NODE_OP_AND, NODE_OP_OR,
        NODE_OP_NOT, NODE_OP_NEG,
        NODE_FUNC_CALL, NODE_FUNC_DEF, NODE_BLOCK,
        NODE_IF, NODE_WHILE
    } node_type_t;

    typedef struct node_s {
        node_type_t type;
        struct node_s *left;
        struct node_s *right;
        struct node_s *else_body;
        struct node_s *body;
        int value;
        char *name;
        struct node_s **children;
        int child_count;
        int cmp_op;
    } node_t;

    typedef struct {
        token_t *tokens;
        int pos;
        int count;
    } parser_t;

    typedef struct {
        char **locals;
        int local_count;
        int label_count;
        FILE *out;
        char *func_name;
    } codegen_ctx_t;

    /* Lexer */
    token_t *tokenize(char *src, int *out_count);
    void lex_grow(lexer_t *lex);
    void lex_add(lexer_t *lex, token_type_t type, char *text, int val);
    void lex_word(lexer_t *lex);
    void lex_number(lexer_t *lex);
    void lex_op(lexer_t *lex);
    void skip_line_comment(lexer_t *lex);
    void skip_block_comment(lexer_t *lex);
    void skip_ws_comments(lexer_t *lex);
    token_type_t kw_type(char *text);

    /* Parser */
    node_t *parse(token_t *tokens, int count);
    node_t *parse_func_def(parser_t *p);
    node_t *parse_block(parser_t *p);
    node_t *parse_stmt(parser_t *p);
    node_t *parse_decl(parser_t *p);
    node_t *parse_return_stmt(parser_t *p);
    node_t *parse_if_stmt(parser_t *p);
    node_t *parse_while_stmt(parser_t *p);
    node_t *parse_assign_or_call(parser_t *p);
    node_t *parse_expr(parser_t *p);
    node_t *parse_or_expr(parser_t *p);
    node_t *parse_and_expr(parser_t *p);
    node_t *parse_eq_expr(parser_t *p);
    node_t *parse_rel_expr(parser_t *p);
    node_t *parse_add_expr(parser_t *p);
    node_t *parse_mul_expr(parser_t *p);
    node_t *parse_unary_expr(parser_t *p);
    node_t *parse_primary_expr(parser_t *p);
    node_t *parse_call_args(parser_t *p, char *name);
    node_t *new_node(node_type_t type);
    token_t *peek(parser_t *p);
    token_t *advance(parser_t *p);
    int expect(parser_t *p, token_type_t type);

    /* Codegen */
    void codegen(node_t *ast, FILE *out);
    void gen_func(node_t *node, codegen_ctx_t *ctx);
    void gen_block(node_t *node, codegen_ctx_t *ctx);
    void gen_stmt(node_t *node, codegen_ctx_t *ctx);
    void gen_assign(node_t *node, codegen_ctx_t *ctx);
    void gen_return(node_t *node, codegen_ctx_t *ctx);
    void gen_if(node_t *node, codegen_ctx_t *ctx);
    void gen_while(node_t *node, codegen_ctx_t *ctx);
    void gen_expr(node_t *node, codegen_ctx_t *ctx);
    void gen_binop(node_t *node, codegen_ctx_t *ctx);
    void gen_call(node_t *node, codegen_ctx_t *ctx);
    void gen_cmp(node_t *node, codegen_ctx_t *ctx);
    int find_local(codegen_ctx_t *ctx, char *name);
    int collect_locals(node_t *block, char **locals, int count);

    /* Main utilities */
    char *read_file(char *path);
    void *xmalloc(size_t size);
    void free_tokens(token_t *tokens, int count);
    void free_node(node_t *node);

#endif
