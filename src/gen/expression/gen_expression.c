/*
** EPITECH PROJECT, 2026
** gen_expression.c
** File description:
** Generation of expression nodes to assembly code
*/
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"
#include "utils/utils.h"

int gen_expression(gen_t *gen, node_t *node)
{
    switch (node->type) {
        case NODE_CONST:
        case NODE_VAR:
            return gen_value(gen, node);
        case NODE_OPERATOR:
            return gen_operator(gen, node);
        default:
            return get_error(EPAR,
                "unsupported node type in expression: '%s'",
                node->name);
    }
    return SUCCESS;
}
