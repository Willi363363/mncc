/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** tests.c - Unit tests for the MNC compiler
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "mncc.h"

Test(lexer, tokenize_int_decl)
{
    int count = 0;
    token_t *tokens = tokenize("int x;", &count);

    cr_assert_eq(count, 4);
    cr_assert_eq(tokens[0].type, TOK_INT);
    cr_assert_eq(tokens[1].type, TOK_IDENT);
    cr_assert_str_eq(tokens[1].text, "x");
    cr_assert_eq(tokens[2].type, TOK_SEMI);
    cr_assert_eq(tokens[3].type, TOK_EOF);
    free_tokens(tokens, count);
}

Test(lexer, tokenize_arithmetic)
{
    int count = 0;
    token_t *tokens = tokenize("a + b * c", &count);

    cr_assert_eq(count, 6);
    cr_assert_eq(tokens[0].type, TOK_IDENT);
    cr_assert_eq(tokens[1].type, TOK_PLUS);
    cr_assert_eq(tokens[2].type, TOK_IDENT);
    cr_assert_eq(tokens[3].type, TOK_MUL);
    cr_assert_eq(tokens[4].type, TOK_IDENT);
    cr_assert_eq(tokens[5].type, TOK_EOF);
    free_tokens(tokens, count);
}

Test(lexer, tokenize_keywords)
{
    int count = 0;
    token_t *tokens = tokenize("if else while return", &count);

    cr_assert_eq(count, 5);
    cr_assert_eq(tokens[0].type, TOK_IF);
    cr_assert_eq(tokens[1].type, TOK_ELSE);
    cr_assert_eq(tokens[2].type, TOK_WHILE);
    cr_assert_eq(tokens[3].type, TOK_RETURN);
    cr_assert_eq(tokens[4].type, TOK_EOF);
    free_tokens(tokens, count);
}

Test(lexer, tokenize_double_char_ops)
{
    int count = 0;
    token_t *tokens = tokenize("== != <= >= && ||", &count);

    cr_assert_eq(count, 7);
    cr_assert_eq(tokens[0].type, TOK_EQEQ);
    cr_assert_eq(tokens[1].type, TOK_NE);
    cr_assert_eq(tokens[2].type, TOK_LE);
    cr_assert_eq(tokens[3].type, TOK_GE);
    cr_assert_eq(tokens[4].type, TOK_AND);
    cr_assert_eq(tokens[5].type, TOK_OR);
    cr_assert_eq(tokens[6].type, TOK_EOF);
    free_tokens(tokens, count);
}

Test(lexer, tokenize_number)
{
    int count = 0;
    token_t *tokens = tokenize("42", &count);

    cr_assert_eq(count, 2);
    cr_assert_eq(tokens[0].type, TOK_NUMBER);
    cr_assert_eq(tokens[0].value, 42);
    cr_assert_eq(tokens[1].type, TOK_EOF);
    free_tokens(tokens, count);
}

Test(lexer, tokenize_skips_line_comment)
{
    int count = 0;
    token_t *tokens = tokenize("int x; // this is a comment\nreturn x;", &count);

    cr_assert_eq(tokens[0].type, TOK_INT);
    cr_assert_eq(tokens[3].type, TOK_RETURN);
    free_tokens(tokens, count);
}

Test(lexer, tokenize_skips_block_comment)
{
    int count = 0;
    token_t *tokens = tokenize("int /* comment */ x;", &count);

    cr_assert_eq(count, 4);
    cr_assert_eq(tokens[0].type, TOK_INT);
    cr_assert_eq(tokens[1].type, TOK_IDENT);
    cr_assert_str_eq(tokens[1].text, "x");
    free_tokens(tokens, count);
}

Test(parser, parse_simple_func)
{
    int count = 0;
    token_t *tokens = tokenize("int main() { return 0; }", &count);
    node_t *ast = parse(tokens, count);

    cr_assert_not_null(ast);
    cr_assert_eq(ast->type, NODE_BLOCK);
    cr_assert_eq(ast->child_count, 1);
    cr_assert_eq(ast->children[0]->type, NODE_FUNC_DEF);
    cr_assert_str_eq(ast->children[0]->name, "main");
    free_tokens(tokens, count);
    free_node(ast);
}

Test(parser, parse_decl_and_assign)
{
    int count = 0;
    token_t *tokens = tokenize("int f() { int x; x = 5; return x; }", &count);
    node_t *ast = parse(tokens, count);
    node_t *func = ast->children[0];
    node_t *block = func->body;

    cr_assert_not_null(ast);
    cr_assert_eq(block->child_count, 3);
    cr_assert_eq(block->children[0]->type, NODE_DECL);
    cr_assert_eq(block->children[1]->type, NODE_ASSIGN);
    cr_assert_eq(block->children[2]->type, NODE_RETURN);
    free_tokens(tokens, count);
    free_node(ast);
}

Test(parser, parse_func_with_params)
{
    int count = 0;
    token_t *tokens = tokenize("int add(int a, int b) { return a; }", &count);
    node_t *ast = parse(tokens, count);
    node_t *func = ast->children[0];

    cr_assert_eq(func->child_count, 2);
    cr_assert_str_eq(func->children[0]->name, "a");
    cr_assert_str_eq(func->children[1]->name, "b");
    free_tokens(tokens, count);
    free_node(ast);
}

Test(codegen, codegen_simple_return)
{
    int count = 0;
    token_t *tokens = tokenize("int main() { return 42; }", &count);
    node_t *ast = parse(tokens, count);
    FILE *out = tmpfile();

    cr_assert_not_null(out);
    codegen(ast, out);
    rewind(out);
    char buf[512];
    size_t n = fread(buf, 1, sizeof(buf) - 1, out);
    buf[n] = '\0';
    cr_assert(strstr(buf, "main:") != NULL);
    cr_assert(strstr(buf, "mov rax, 42") != NULL);
    fclose(out);
    free_tokens(tokens, count);
    free_node(ast);
}
