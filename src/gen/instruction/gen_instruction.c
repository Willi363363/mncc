/*
** EPITECH PROJECT, 2026
** gen_instruction.c
** File description:
** Generation of instruction nodes to assembly code
*/
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"
#include "utils/utils.h"

int gen_instruction(gen_t *gen, node_t *node)
{
    switch (node->type) {
        case NODE_RETURN:
            return gen_return(gen, node);
        case NODE_IF:
            return gen_if(gen, node);
        case NODE_DECLARATION:
            return gen_declaration(gen, node);
        case NODE_ASSIGN:
            return gen_assignement(gen, node);
        case NODE_BLOCK:
            return gen_block(gen, node);
        default:
            return get_error(EGEN,
                "unsupported node type in instruction: '%s'",
                node->name);
    }
    return SUCCESS;
}
