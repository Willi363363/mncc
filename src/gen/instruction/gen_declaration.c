/*
** EPITECH PROJECT, 2026
** gen_declaration.c
** File description:
** Generation of declaration instruction node to assembly code
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"
#include "utils/utils.h"

static int create_variable(gen_t *gen, char *name)
{
    stack_data_t *data = malloc(sizeof(stack_data_t));

    if (!data)
        return get_error(ENOMEM, "stack variable allocation");
    data->name = name;
    data->offset = gen->stack->variables->count * 8;
    array_push(gen->stack->variables, data);
    return SUCCESS;
}

int gen_declaration(gen_t *gen, node_t *node)
{
    fprintf(gen->out, "    sub rsp, 8\n");
    if (create_variable(gen, node->name) != SUCCESS)
        return ERROR;
    if (node->childs->count > 0)
        return gen_assignement(gen, node);
    return SUCCESS;
}
