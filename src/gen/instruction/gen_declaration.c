/*
** EPITECH PROJECT, 2026
** gen_declaration.c
** File description:
** Generation of declaration instruction node to assembly code
*/
#include <errno.h>
#include <stdlib.h>
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

static int create_variable(gen_t *gen, char *name)
{
    variable_t *data = malloc(sizeof(variable_t));

    if (!data)
        return get_error(ENOMEM, "stack variable allocation");
    data->name = strdup(name);
    data->offset = (gen->variables->count + 1) * 8;
    array_push(gen->variables, data);
    return SUCCESS;
}

int gen_declaration(gen_t *gen, node_t *node)
{
    int offset = 0;

    gen->write(gen, "sub rsp, 8");
    if (!node->left || !node->left->name)
        return get_error(EGEN, "declaration node missing variable name");
    if (create_variable(gen, node->left->name) != SUCCESS)
        return ERROR;
    if (!node->right) {
        offset = get_offset(gen, node->left->name);
        if (offset < 0)
            return ERROR;
        if (offset > 0)
            gen->write(gen, "mov [rbp - 0x%X], 0", offset);
        else
            gen->write(gen, "mov [rbp], 0");
    }
    if (node->right)
        return gen_assignement(gen, node);
    return SUCCESS;
}
