/*
** EPITECH PROJECT, 2026
** get_expression_size.c
** File description:
** Get the size of an expression in tokens for the parser
*/
#include <stdbool.h>
#include <stdio.h>
#include "lexer/token.h"
#include "parser/parser.h"

static bool is_value_token(token_t *token)
{
    return token->type == TOK_NUMBER || token->type == TOK_IDENT ||
        token->type == TOK_STR;
}

static bool is_expression_token(token_t *token, size_t *depth)
{
    if (token->type == TOK_LPAREN) {
        (*depth)++;
        return true;
    }
    if (*depth && token->type == TOK_RPAREN) {
        (*depth)--;
        return true;
    }
    if (*depth && token->type == TOK_COMMA)
        return true;
    return is_operator_token(token) || is_value_token(token);
}

ssize_t get_expression_size(parser_t *parser)
{
    size_t size = 0;
    size_t cursor = parser->cursor;
    token_t *token = parser_peek(parser);
    size_t depth = 0;

    while (token && is_expression_token(token, &depth)) {
        size++;
        parser_next(parser);
        token = parser_peek(parser);
    }
    parser->cursor = cursor;
    return depth < 0 ? NOIDX : size;
}
