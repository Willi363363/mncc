/*
** EPITECH PROJECT, 2026
** tests_lexer.c
** File description:
** Unit tests for the lexer component
*/
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "utils/array.h"

Test(lexer, tokenize_simple_expression)
{
    lexer_t *lexer = lexer_create("42 + 24");
    token_t *token = NULL;

    cr_assert_not_null(lexer);
    cr_assert_eq(lexer_run(lexer), SUCCESS);
    cr_assert_eq(lexer->tokens->count, 4);
    token = (token_t *)lexer->tokens->data[0];
    cr_assert_eq(token->type, TOK_NUMBER);
    cr_assert_str_eq(token->value, "42");
    token = (token_t *)lexer->tokens->data[1];
    cr_assert_eq(token->type, TOK_PLUS);
    cr_assert_str_eq(token->value, "+");
    token = (token_t *)lexer->tokens->data[2];
    cr_assert_eq(token->type, TOK_NUMBER);
    cr_assert_str_eq(token->value, "24");
    token = (token_t *)lexer->tokens->data[3];
    cr_assert_eq(token->type, TOK_EOF);
    lexer_destroy(lexer);
}

Test(lexer, tokenize_with_comments)
{
    lexer_t *lexer = lexer_create("42 + 24 // this is a comment");
    token_t *token = NULL;

    cr_assert_not_null(lexer);
    cr_assert_eq(lexer_run(lexer), SUCCESS);
    cr_assert_eq(lexer->tokens->count, 4);
    token = (token_t *)lexer->tokens->data[0];
    cr_assert_eq(token->type, TOK_NUMBER);
    cr_assert_str_eq(token->value, "42");
    token = (token_t *)lexer->tokens->data[1];
    cr_assert_eq(token->type, TOK_PLUS);
    cr_assert_str_eq(token->value, "+");
    token = (token_t *)lexer->tokens->data[2];
    cr_assert_eq(token->type, TOK_NUMBER);
    cr_assert_str_eq(token->value, "24");
    token = (token_t *)lexer->tokens->data[3];
    cr_assert_eq(token->type, TOK_EOF);
    lexer_destroy(lexer);
}

Test(lexer, tokenize_with_block_comments)
{
    lexer_t *lexer = lexer_create("42 + 24 /* this is a block comment */");
    token_t *token = NULL;

    cr_assert_not_null(lexer);
    cr_assert_eq(lexer_run(lexer), SUCCESS);
    cr_assert_eq(lexer->tokens->count, 4);
    token = (token_t *)lexer->tokens->data[0];
    cr_assert_eq(token->type, TOK_NUMBER);
    cr_assert_str_eq(token->value, "42");
    token = (token_t *)lexer->tokens->data[1];
    cr_assert_eq(token->type, TOK_PLUS);
    cr_assert_str_eq(token->value, "+");
    token = (token_t *)lexer->tokens->data[2];
    cr_assert_eq(token->type, TOK_NUMBER);
    cr_assert_str_eq(token->value, "24");
    token = (token_t *)lexer->tokens->data[3];
    cr_assert_eq(token->type, TOK_EOF);
    lexer_destroy(lexer);
}

Test(lexer, tokenize_invalid_character)
{
    lexer_t *lexer = lexer_create("42 + 24 @");
    int result = 0;

    cr_assert_not_null(lexer);
    result = lexer_run(lexer);
    cr_assert_eq(result, ELEX);
    lexer_destroy(lexer);
}
