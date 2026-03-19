/*
** EPITECH PROJECT, 2026
** tests_parser.c
** File description:
** Unit tests for the parser component
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/array.h"

Test(parser, token_match_operator_plus)
{
    token_t *tokens[3] = {token_create(TOK_PLUS, "+"),
        token_create(TOK_EOF, NULL),
        token_create(TOK_EOF, NULL)};
    operator_type_t op = OP_ADD;

    cr_assert(tokens_match_operator(tokens, op));
}

Test(parser, token_match_operator_equal)
{
    token_t *tokens[3] = {token_create(TOK_EQ, "="),
        token_create(TOK_EQ, "="),
        token_create(TOK_EOF, NULL)};
    operator_type_t op = OP_EQUAL;

    cr_assert(tokens_match_operator(tokens, op));
}

Test(parser, parse_simple_expression)
{
    lexer_t *lexer = lexer_create();
    parser_t *parser = parser_create(lexer);
    node_t *node = NULL;

    cr_assert_not_null(parser);
    array_push(lexer->tokens, token_create(TOK_NUMBER, "42"));
    array_push(lexer->tokens, token_create(TOK_PLUS, "+"));
    array_push(lexer->tokens, token_create(TOK_NUMBER, "24"));
    array_push(lexer->tokens, token_create(TOK_EOF, NULL));
    node = parse_expression(parser);
    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_OPERATOR);
    cr_assert_eq(node->op, OP_ADD);
    cr_assert_not_null(node->left);
    cr_assert_eq(node->left->type, NODE_CONST);
    cr_assert_eq(node->left->value, 42);
    cr_assert_not_null(node->right);
    cr_assert_eq(node->right->type, NODE_CONST);
    cr_assert_eq(node->right->value, 24);
    parser_destroy(parser);
}

Test(parser, parse_priority_expression)
{
    lexer_t *lexer = lexer_create();
    parser_t *parser = parser_create(lexer);
    node_t *node = NULL;

    cr_assert_not_null(parser);
    array_push(lexer->tokens, token_create(TOK_NUMBER, "42"));
    array_push(lexer->tokens, token_create(TOK_PLUS, "+"));
    array_push(lexer->tokens, token_create(TOK_NUMBER, "24"));
    array_push(lexer->tokens, token_create(TOK_MUL, "*"));
    array_push(lexer->tokens, token_create(TOK_NUMBER, "2"));
    array_push(lexer->tokens, token_create(TOK_EOF, NULL));
    node = parse_expression(parser);
    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_OPERATOR);
    cr_assert_eq(node->op, OP_ADD);
    cr_assert_not_null(node->left);
    cr_assert_eq(node->left->type, NODE_CONST);
    cr_assert_eq(node->left->value, 42);
    cr_assert_not_null(node->right);
    cr_assert_eq(node->right->type, NODE_OPERATOR);
    cr_assert_eq(node->right->op, OP_MUL);
    cr_assert_not_null(node->right->left);
    cr_assert_eq(node->right->left->type, NODE_CONST);
    cr_assert_eq(node->right->left->value, 24);
    cr_assert_not_null(node->right->right);
    cr_assert_eq(node->right->right->type, NODE_CONST);
    cr_assert_eq(node->right->right->value, 2);
    parser_destroy(parser);
}
