/*
** EPITECH PROJECT, 2026
** gen_value.c
** File description:
** Generation of value nodes to assembly code
*/
#include <string.h>
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"
#include "utils/utils.h"

static int get_offset(gen_t *gen, const char *name)
{
    variable_t *data = NULL;

    for (int i = 0; i < gen->variables->count; i++) {
        data = gen->variables->data[i];
        if (strcmp(data->name, name) == 0)
            return data->offset;
    }
    get_error(EGEN, "variable '%s' not found in stack", name);
    return -1;
}

int gen_value_in_register(gen_t *gen, node_t *node, int i)
{
    const char *reg = gen_get_register(i);
    int offset = 0;

    if (node->type == NODE_CONST) {
        gen->write(gen, "mov %s, 0x%X", reg, node->value);
        return SUCCESS;
    }
    if (node->type == NODE_VAR) {
        offset = get_offset(gen, node->name);
        if (offset < 0)
            return ERROR;
        if (offset > 0)
            gen->write(gen, "mov %s, [rbp - 0x%X]", reg, offset);
        else
            gen->write(gen, "mov %s, [rbp]", reg);
    }
    return SUCCESS;
}
