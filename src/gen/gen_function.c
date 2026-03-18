/*
** EPITECH PROJECT, 2026
** gen_function.c
** File description:
** Generation of function node to assembly code
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"
#include "utils/utils.h"

static variable_t *create_variable(gen_t *gen, char *name)
{
    variable_t *data = malloc(sizeof(variable_t));

    if (!data) {
        get_error(ENOMEM, "stack variable allocation");
        return NULL;
    }
    data->name = strdup(name);
    data->offset = (gen->variables->count + 1) * 8;
    array_push(gen->variables, data);
    return data;
}

static void put_arguments_in_stack(gen_t *gen, node_t *node)
{
    const char *reg = NULL;
    node_t *arg = NULL;
    variable_t *var = NULL;

    for (int i = 0; i < node->childs->count - 1; i++) {
        reg = gen_get_register(i);
        arg = node->childs->data[i];
        var = create_variable(gen, arg->name);
        fprintf(gen->out, "    sub rsp, 0x%X\n", var->offset);
        if (var->offset > 0)
            fprintf(gen->out, "    mov [rbp - 0x%X], %s\n", var->offset, reg);
        else
            fprintf(gen->out, "    mov [rbp], %s\n", reg);
    }
}

static void gen_function_body(gen_t *gen, node_t *node)
{
    node_t *child = NULL;

    for (int i = 0; i < node->childs->count; i++) {
        child = node->childs->data[i];
        if (child->type == NODE_BLOCK && gen_instruction(gen, child) != SUCCESS)
            return;
    }
}

int gen_function(gen_t *gen, node_t *node)
{
    variable_t *data = NULL;

    gen->variables = array_create((array_element_destroy_t)free);
    if (!gen->variables)
        return get_error(ENOMEM, "generator function variables allocation");
    fprintf(gen->out, "%s:\n", node->name);
    fprintf(gen->out, "    push rbp\n    mov rbp, rsp\n");
    put_arguments_in_stack(gen, node);
    gen_function_body(gen, node);
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
