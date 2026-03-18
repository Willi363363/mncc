/*
** EPITECH PROJECT, 2026
** tests_parser.c
** File description:
** Unit tests for the parser component
*/

#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include <criterion/redirect.h>
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "parser/parser.h"
#include "utils/array.h"

Test(parser, parse_simple_instruction)
{
    lexer_t *lexer = lexer_create();
    parser_t *parser = parser_create(lexer);
    node_t *node = NULL;
    node_t *block = NULL;

    cr_assert_not_null(parser);
    array_push(lexer->tokens, token_create(TOK_RETURN, "return"));
    array_push(lexer->tokens, token_create(TOK_INT, "24"));
    array_push(lexer->tokens, token_create(TOK_SEMI, NULL));
    node = parse_instruction(parser);
    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_RETURN);
    cr_assert_not_null(node->childs);
    cr_assert_eq(node->childs->count, 1);
    block = (node_t *)node->childs->data[0];
    cr_assert_eq((block)->type, NODE_CONST);
    cr_assert_eq((block)->value, 24);
    parser_destroy(parser);
}

Test(parser, parse_function_declaration)
{
    lexer_t *lexer = lexer_create();
    parser_t *parser = parser_create(lexer);
    node_t *node = NULL;
    node_t *block = NULL;
    node_t *return_node = NULL;

    cr_assert_not_null(parser);
    array_push(lexer->tokens, token_create(TOK_INT, "int"));
    array_push(lexer->tokens, token_create(TOK_IDENT, "main"));
    array_push(lexer->tokens, token_create(TOK_LPAREN, NULL));
    array_push(lexer->tokens, token_create(TOK_RPAREN, NULL));
    array_push(lexer->tokens, token_create(TOK_LBRACE, NULL));
    array_push(lexer->tokens, token_create(TOK_RETURN, "return"));
    array_push(lexer->tokens, token_create(TOK_INT, "0"));
    array_push(lexer->tokens, token_create(TOK_SEMI, NULL));
    array_push(lexer->tokens, token_create(TOK_RBRACE, NULL));
    node = parse_function(parser);
    cr_assert_not_null(node);
    cr_assert_eq(node->type, NODE_FUNCTION);
    cr_assert_str_eq(node->name, "main");
    cr_assert_eq(node->data_type, DATA_INT);
    cr_assert_not_null(node->childs);
    cr_assert_eq(node->childs->count, 1);
    block = (node_t *)node->childs->data[0];
    cr_assert_eq((block)->type, NODE_BLOCK);
    cr_assert_not_null((block)->childs);
    return_node = (node_t *)block->childs->data[0];
    cr_assert_eq((return_node)->type, NODE_RETURN);
    cr_assert_not_null(return_node->childs);
    cr_assert_eq(((node_t *)(return_node->childs->data[0]))->type, NODE_CONST);
    cr_assert_eq(((node_t *)(return_node->childs->data[0]))->value, 0);
    parser_destroy(parser);
}
