/*
** EPITECH PROJECT, 2026
** gen_function.c
** File description:
** Generation of function node to assembly code
*/
#include <errno.h>
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

    if (node->childs->count == 1)
        return;
    gen->add_section(gen, "arguments");
    for (int i = 0; i < node->childs->count - 1; i++) {
        reg = gen_get_register(i);
        arg = node->childs->data[i];
        var = create_variable(gen, arg->name);
        gen->write(gen, "sub rsp, 0x%X", var->offset);
        if (var->offset > 0)
            gen->write(gen, "mov [rbp - 0x%X], %s", var->offset, reg);
        else
            gen->write(gen, "mov [rbp], %s", reg);
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

static void write_start(gen_t *gen, node_t *node)
{
    gen->add_section(gen,
        "function: %s - %d arguments",
        node->name,
        node->childs->count - 1);
    gen->write(gen, "%s:", node->name);
    gen->indentation++;
    gen->write(gen, "push rbp");
    gen->write(gen, "mov rbp, rsp");
}

static void write_end(gen_t *gen)
{
    gen->add_section(gen, "end");
    gen->write(gen, ".return:");
    gen->write(gen, "leave");
    gen->write(gen, "ret");
    gen->indentation--;
}

int gen_function(gen_t *gen, node_t *node)
{
    variable_t *data = NULL;

    gen->variables = array_create((array_element_destroy_t)free);
    if (!gen->variables)
        return get_error(ENOMEM, "generator function variables allocation");
    write_start(gen, node);
    put_arguments_in_stack(gen, node);
    gen->add_section(gen, "body");
    gen_function_body(gen, node);
    write_end(gen);
    for (int i = 0; i < gen->variables->count; i++) {
        data = gen->variables->data[i];
        free(data->name);
    }
    array_destroy(gen->variables, 1);
    gen->variables = NULL;
    return SUCCESS;
}
