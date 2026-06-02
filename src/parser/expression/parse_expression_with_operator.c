/*
** EPITECH PROJECT, 2026
** parse_expression_with_operator.c
** File description:
** Parse an expression with an operator
*/
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/utils.h"

static node_t *create_operator_node(token_t *token)
{
    node_t *node = node_create(NODE_OPERATOR);

    if (!node)
        return print_error(EMEM, NULL, "parser operator node allocation");
    node->op = token_to_operator(token);
    return node;
}

node_t *parse_expression_with_operator(parser_t *parser, size_t size)
{
    size_t op_index = get_operator_offset(parser, size);
    token_t *token = parser_at(parser, parser->cursor + op_index);
    node_t *node = create_operator_node(token);

    if (!node)
        return NULL;
    node->left = parse_expression_with_size(parser, op_index);
    if (!node->left)
        return NULL;
    parser->cursor++;
    node->right = parse_expression(parser);
    if (!node->right)
        return NULL;
    return node;
}
