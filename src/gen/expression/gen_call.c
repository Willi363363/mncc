/*
** EPITECH PROJECT, 2026
** gen_value.c
** File description:
** Generation of value nodes to assembly code
*/
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"

static int load_arguments(gen_t *gen, node_t *node)
{
    for (int i = 1; i < node->childs->count; i++) {
        gen->write(gen, "pop %s", gen_get_register(i));
    }
    return SUCCESS;
}

int gen_call(gen_t *gen, node_t *node)
{
    gen->write(gen, "; call: %s", node->name);
    for (int i = node->childs->count - 1; i >= 0; i--) {
        if (gen_expression(gen, node->childs->data[i]) != SUCCESS)
            return ERROR;
        if (i != 0)
            gen->write(gen, "push rax");
    }
    load_arguments(gen, node);
    gen->write(gen, "call %s", node->name);
    return SUCCESS;
}
