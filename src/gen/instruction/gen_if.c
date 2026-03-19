/*
** EPITECH PROJECT, 2026
** gen_if.c
** File description:
** Generation of if instruction node to assembly code
*/
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"

int gen_if(gen_t *gen, node_t *node)
{
    gen->write(gen, "; if statement");
    gen_expression(gen, node->childs->data[0]);
    gen->write(gen, "cmp rax, 0");
    gen->write(gen, "je .else_%s", node->name);
    gen->indentation++;
    gen_block(gen, node->childs->data[1]);
    gen->write(gen, "jmp .endif_%s", node->name);
    gen->indentation--;
    gen->write(gen, ".else_%s:", node->name);
    if (node->childs->count > 2) {
        gen_block(gen, node->childs->data[2]);
    }
    gen->write(gen, ".endif_%s:", node->name);
    return SUCCESS;
}
