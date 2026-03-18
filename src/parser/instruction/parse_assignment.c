/*
** EPITECH PROJECT, 2026
** parse_assignment.c
** File description:
** Assignment instruction parsing function with static helpers
*/
#include <errno.h>
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/array.h"
#include "utils/utils.h"

static int parse_lhs(parser_t *parser, node_t *assign_node)
{
    node_t *lhs = parse_expression(parser);

    if (!lhs)
        return get_error(ENOMEM, "parser assignment node allocation");
    if (lhs->type != NODE_VAR) {
        node_destroy(lhs);
        return get_error(EPAR,
            "invalid assignment left-hand side: expected variable");
    }
    assign_node->left = lhs;
    return SUCCESS;
}

static int parse_rhs(parser_t *parser, node_t *assign_node)
{
    node_t *rhs = parse_expression(parser);

    if (!rhs)
        return get_error(ENOMEM, "parser assignment node allocation");
    assign_node->left = rhs;
    return SUCCESS;
}

node_t *parse_assignment(parser_t *parser)
{
    node_t *node = node_create(NODE_ASSIGN);

    if (!node)
        return NULL;
    if (parse_lhs(parser, node) != SUCCESS) {
        node_destroy(node);
        return NULL;
    }
    if (!parser_match(parser, TOK_EQ)) {
        node_destroy(node);
        get_error(EPAR,
            "invalid assignment operator: got '%s'",
            parser_peek(parser)->value);
        return NULL;
    }
    if (parse_rhs(parser, node) != SUCCESS) {
        node_destroy(node);
        return NULL;
    }
    return node;
}
