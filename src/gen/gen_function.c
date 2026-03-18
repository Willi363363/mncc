/*
** EPITECH PROJECT, 2026
** gen_function.c
** File description:
** Generation of function node to assembly code
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"
#include "utils/utils.h"

int gen_function(gen_t *gen, node_t *node)
{
    variable_t *data = NULL;

    gen->variables = array_create((array_element_destroy_t)free);
    if (!gen->variables)
        return get_error(ENOMEM, "generator function variables allocation");
    fprintf(gen->out, "%s:\n", node->name);
    fprintf(gen->out, "    push rbp\n    mov rbp, rsp\n");
    gen_block(gen, node->childs->data[0]);
    fprintf(gen->out, "    leave\n    ret\n");
    fprintf(gen->out, "\n");
    for (int i = 0; i < gen->variables->count; i++) {
        data = gen->variables->data[i];
        free(data->name);
    }
    array_destroy(gen->variables, 1);
    gen->variables = NULL;
    return SUCCESS;
}
