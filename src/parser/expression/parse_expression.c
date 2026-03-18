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
    if (*depth && token->type == TOK_RPAREN) {
        (*depth)--;
        return true;
    }
    if (*depth && token->type == TOK_COMMA)
        return true;
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
    if (depth < 0)
        return -1;
    return size;
}

static bool contains_operator(parser_t *parser, int size)
{
    int cursor = parser->cursor;
    token_t *token = NULL;
    bool result = false;
    int depth = 0;

    for (int i = 0; i < size; i++) {
        token = parser_peek(parser);
        if (token->type == TOK_LPAREN)
            depth++;
        if (token->type == TOK_RPAREN)
            depth--;
        if (is_operator_token(token) && depth == 0) {
            result = true;
            break;
        }
        parser_next(parser);
    }
    parser->cursor = cursor;
    return result;
}

static bool is_parenthese_surrounded(parser_t *parser, int size)
{
    token_t *first = parser_peek(parser);
    token_t *last = parser_at(parser, parser->cursor + size - 1);

    if (!first || !last)
        return false;
    return first->type == TOK_LPAREN && last->type == TOK_RPAREN;
}

static node_t *parse_parenthesized_expression(parser_t *parser, int size)
{
    node_t *node = NULL;

    parser->cursor++;
    node = parse_sized_expression(parser, size - 2);
    if (!node) {
        get_error(EPAR,
            "invalid expression '%s'",
            parser_peek(parser) ? parser_peek(parser)->value : "end of input");
        return NULL;
    }
    if (!parser_match(parser, TOK_RPAREN)) {
        node_destroy(node);
        get_error(EPAR,
            "expected ')' at the end of parenthesized expression, got '%s'",
            parser_peek(parser) ? parser_peek(parser)->value : "end of input");
        return NULL;
    }
    parser->cursor++;
    return node;
}

node_t *parse_sized_expression(parser_t *parser, int size)
{
    node_t *node = NULL;

    if (is_parenthese_surrounded(parser, size))
        return parse_parenthesized_expression(parser, size);
    if (contains_operator(parser, size))
        node = parse_operator(parser, size);
    else
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

    if (size <= 0) {
        get_error(EPAR,
            "unexpected token '%s' while parsing expression",
            parser_peek(parser) ? parser_peek(parser)->value : "end of input");
        return NULL;
    }
    return parse_sized_expression(parser, size);
}
