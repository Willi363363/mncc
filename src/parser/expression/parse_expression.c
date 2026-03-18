/*
** EPITECH PROJECT, 2026
** parse_expression.c
** File description:
** Expression parsing function
*/
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/array.h"
#include "utils/utils.h"

static int is_operator_token(token_t *token)
{
    if (token->type == TOK_PLUS || token->type == TOK_MINUS)
        return true;
    if (token->type == TOK_MUL || token->type == TOK_DIV)
        return true;
    return false;
}

static int is_value_token(token_t *token)
{
    return token->type == TOK_NUMBER || token->type == TOK_IDENT;
}

static int is_expression_token(token_t *token, int *depth)
{
    if (token->type == TOK_LPAREN) {
        (*depth)++;
        return true;
    }
    if (token->type == TOK_RPAREN) {
        (*depth)--;
        return *depth >= 0;
    }
    return is_operator_token(token) || is_value_token(token);
}

static int expression_size(parser_t *parser)
{
    int size = 0;
    int cursor = parser->cursor;
    token_t *token = NULL;
    int depth = 0;

    while (true) {
        token = parser_peek(parser);
        if (!token || !is_expression_token(token, &depth))
            break;
        size++;
        parser_next(parser);
    }
    parser->cursor = cursor;
    return size;
}

static bool contains_operator(parser_t *parser, int size)
{
    int cursor = parser->cursor;
    token_t *token = NULL;
    bool result = false;

    for (int i = 0; i < size; i++) {
        token = parser_peek(parser);
        if (is_operator_token(token)) {
            result = true;
            break;
        }
        parser_next(parser);
    }
    parser->cursor = cursor;
    return result;
}

node_t *parse_sized_expression(parser_t *parser, int size)
{
    node_t *node = NULL;
    bool is_operator = contains_operator(parser, size);

    if (is_operator) {
        node = parse_operator(parser, size);
        if (!node) {
            get_error(EPAR,
                "invalid operator in expression '%s'",
                parser_peek(parser) ? parser_peek(parser)->value : "end of input");
            return NULL;
        }
    } else
        node = parse_value(parser);
    if (!node) {
        get_error(EPAR,
            "invalid expression '%s'",
            parser_peek(parser) ? parser_peek(parser)->value : "end of input");
        return NULL;
    }
    return node;
}

node_t *parse_expression(parser_t *parser)
{
    int size = expression_size(parser);

    if (size == 0) {
        get_error(EPAR,
            "unexpected token '%s'",
            parser_peek(parser) ? parser_peek(parser)->value : "end of input");
        return NULL;
    }
    return parse_sized_expression(parser, size);
}
