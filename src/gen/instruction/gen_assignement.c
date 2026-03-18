/*
** EPITECH PROJECT, 2026
** gen_assignement.c
** File description:
** Generation of assignement instruction node to assembly code
*/
#include <stdio.h>
#include <string.h>
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"
#include "utils/utils.h"

static int get_offset(gen_t *gen, const char *name)
{
    stack_data_t *data = NULL;

    for (int i = 0; i < gen->stack->variables->count; i++) {
        data = gen->stack->variables->data[i];
        if (strcmp(data->name, name) == 0)
            return data->offset;
    }
    get_error(EPAR, "variable '%s' not found in stack", name);
    return -1;
}

int gen_assignement(gen_t *gen, node_t *node)
{
    int offset = get_offset(gen, node->name);

    if (offset < 0)
        return ERROR;
    if (gen_expression(gen, node->childs->data[0]) != SUCCESS)
        return ERROR;
    fprintf(gen->out, "    mov [rbp - %d], rax\n", offset);
    return SUCCESS;    
}
