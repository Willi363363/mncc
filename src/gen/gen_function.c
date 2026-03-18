/*
** EPITECH PROJECT, 2026
** gen_function.c
** File description:
** Generation of function node to assembly code
*/
#include <stdio.h>
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"

int gen_function(gen_t *gen, node_t *node)
{
    fprintf(gen->out, "%s:\n", node->name);
    fprintf(gen->out, "    push rbp\n    mov rbp, rsp\n");
    gen_block(gen, node->childs->data[0]);
    fprintf(gen->out, "    leave\n    ret\n");
    fprintf(gen->out, "\n");
    return SUCCESS;
}
