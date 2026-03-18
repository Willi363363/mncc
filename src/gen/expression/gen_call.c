/*
** EPITECH PROJECT, 2026
** gen_value.c
** File description:
** Generation of value nodes to assembly code
*/
#include <stdio.h>
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"

int gen_call(gen_t *gen, node_t *node)
{
    for (int i = node->childs->count - 1; i >= 0; i--) {
        if (gen_expression(gen, node->childs->data[i]) != SUCCESS)
            return ERROR;
        fprintf(gen->out, "    push rax\n");
    }
    fprintf(gen->out, "    call %s\n", node->name);

    fprintf(gen->out, "    add rsp, 0x%X\n", node->childs->count * 8);
    return SUCCESS;
}
