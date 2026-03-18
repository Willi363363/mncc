/*
** EPITECH PROJECT, 2026
** parse_operator.c
** File description:
** Operator expression parsing function with static helpers
*/
#include <errno.h>
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/array.h"
#include "utils/utils.h"

static operator_type_t token_to_operator(token_type_t type)
{
    switch (type) {
        case TOK_PLUS:
            return OP_ADD;
        case TOK_MINUS:
            return OP_SUB;
        case TOK_MUL:
            return OP_MUL;
        case TOK_DIV:
            return OP_DIV;
        default:
            return OP_INVALID;
    }
}

static token_type_t get_operator_token_type(operator_type_t op)
{
    switch (op) {
        case OP_ADD:
            return TOK_PLUS;
        case OP_SUB:
            return TOK_MINUS;
        case OP_MUL:
            return TOK_MUL;
        case OP_DIV:
            return TOK_DIV;
        default:
            return TOK_EOF;
    }
}

static int get_operator_offset(parser_t *parser, int size, operator_type_t op)
{
    int cursor = parser->cursor;
    token_type_t type = get_operator_token_type(op);
    token_t *token = NULL;

    for (int offset = 0; offset < size; offset++) {
        token = parser_peek(parser);
        if (token->type == type) {
            parser->cursor = cursor;
            return offset;
        }
        parser_next(parser);
    }
    parser->cursor = cursor;
    return -1;
}

static int parse_left_right(parser_t *parser, node_t *node, int offset)
{
    node->left = parse_sized_expression(parser, offset);
    if (!node->left)
        return EPAR;
    if (parser_peek(parser)->type != TOK_EOF) {
        get_error(EPAR,
            "unexpected token after operator",
            "expected end of expression but got '%s'",
            parser_peek(parser) ? parser_peek(parser)->value : "end of input");
        return EPAR;
    }
    parser->cursor++;
    node->right = parse_expression(parser);
    if (!node->right)
        return EPAR;
    return SUCCESS;
}

static node_t *create_operator_node(parser_t *parser, int offset)
{
    token_t *token = parser_at(parser, parser->cursor + offset);
    node_t *node = node_create(NODE_OPERATOR);

    if (!node) {
        get_error(ENOMEM, NULL, "parser operator node allocation");
        return NULL;
    }
    node->op = token_to_operator(token->type);
    token->type = TOK_EOF;
    if (parse_left_right(parser, node, offset) != SUCCESS) {
        node_destroy(node);
        return NULL;
    }
    token->type = get_operator_token_type(node->op);
    return node;
}

node_t *parse_operator(parser_t *parser, int size)
{
    int offset = -1;

    for (int i = 0; i < OPERATOR_COUNT; i++) {
        offset = get_operator_offset(parser, size, i);
        if (offset != -1)
            return create_operator_node(parser, offset);
    }
    get_error(EPAR,
        "invalid operator expression",
        "expected an operator but got '%s'",
        parser_peek(parser) ? parser_peek(parser)->value : "end of input");
    return NULL;
}
