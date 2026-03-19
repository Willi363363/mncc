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

static int
parse_left_right(parser_t *parser, node_t *node, int op_index, int op_size)
{
    node->left = parse_sized_expression(parser, op_index);
    if (!node->left)
        return EPAR;
    parser->cursor += op_size;
    node->right = parse_expression(parser);
    if (!node->right)
        return EPAR;
    return SUCCESS;
}

static node_t *create_operator_node(parser_t *parser, int op_index)
{
    token_t **op_tokens = parser_tokens_peek(parser) + op_index;
    node_t *node = node_create(NODE_OPERATOR);

    if (!node) {
        get_error(ENOMEM, NULL, "parser operator node allocation");
        return NULL;
    }
    node->op = tokens_to_operator(op_tokens);
    if (parse_left_right(parser, node, op_index, get_operator_size(node->op))) {
        node_destroy(node);
        return NULL;
    }
    return node;
}

node_t *parse_operator(parser_t *parser, int size)
{
    int op_index = -1;

    for (int i = 0; i < OPERATOR_COUNT; i++) {
        op_index = get_operator_offset(parser, size, i);
        if (op_index != -1)
            return create_operator_node(parser, op_index);
    }
    get_error(EPAR,
        "expected an operator, got '%s'",
        parser_peek(parser) ? parser_peek(parser)->value : "end of input");
    return NULL;
}
