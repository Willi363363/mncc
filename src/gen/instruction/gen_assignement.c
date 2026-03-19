/*
** EPITECH PROJECT, 2026
** gen_assignement.c
** File description:
** Generation of assignement instruction node to assembly code
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

int gen_assignement(gen_t *gen, node_t *node)
{
    int offset = get_offset(gen, node->left->name);

    if (offset < 0)
        return ERROR;
    if (gen_expression(gen, node->right) != SUCCESS)
        return ERROR;
    gen->write(gen, "mov [rbp - 0x%X], rax", offset);
    return SUCCESS;
}
