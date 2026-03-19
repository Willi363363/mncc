/*
** EPITECH PROJECT, 2026
** gen_return.c
** File description:
** Generation of return instruction node to assembly code
*/
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"

int gen_return(gen_t *gen, node_t *node)
{
    if (node->childs->count == 0) {
        gen->write(gen, "mov rax, 0");
        return SUCCESS;
    }
    gen_expression(gen, node->childs->data[0]);
    gen->write(gen, "jmp .return");
    return SUCCESS;
}
