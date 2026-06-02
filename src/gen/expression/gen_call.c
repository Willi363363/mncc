/*
** EPITECH PROJECT, 2026
** gen_call.c
** File description:
** Generation of call nodes to assembly code
*/
#include <stdio.h>
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"

static status_t load_arguments(gen_t *gen, node_t *node)
{
    for (size_t i = 1; i < node->childs->count; i++) {
        gen->write(gen, "pop %s", gen_get_register(i));
    }
    return SUCCESS;
}

status_t gen_call(gen_t *gen, node_t *node)
{
    gen->write(gen, "; call: %s", node->name);
    for (ssize_t i = node->childs->count - 1; i >= 0; i--) {
        if (gen_expression(gen, node->childs->data[i]) != SUCCESS)
            return EGEN;
        if (i != 0)
            gen->write(gen, "push rax");
    }
    load_arguments(gen, node);
    gen->write(gen, "call %s", node->name);
    return SUCCESS;
}
