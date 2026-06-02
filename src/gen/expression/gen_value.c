/*
** EPITECH PROJECT, 2026
** gen_value.c
** File description:
** Generation of value nodes to assembly code
*/
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"

status_t gen_value_in_register(gen_t *gen, node_t *node, int i)
{
    const char *reg = gen_get_register(i);
    ssize_t offset = 0;

    if (node->type == NODE_CONST) {
        gen->write(gen, "mov %s, 0x%X", reg, node->value);
        return SUCCESS;
    }
    if (node->type == NODE_VAR) {
        offset = gen_get_var_offset(gen, node->name);
        if (offset < 0)
            return EGEN;
        if (offset > 0)
            gen->write(gen, "mov %s, [rbp - 0x%X]", reg, offset);
        else
            gen->write(gen, "mov %s, [rbp]", reg);
    }
    return SUCCESS;
}
