/*
** EPITECH PROJECT, 2026
** gen_assignement.c
** File description:
** Generation of assignement instruction node to assembly code
*/
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"

status_t gen_assignement(gen_t *gen, node_t *node)
{
    int offset = gen_get_var_offset(gen, node->left->name);

    if (offset < 0)
        return EGEN;
    if (gen_expression(gen, node->right) != SUCCESS)
        return EGEN;
    gen->write(gen, "mov [rbp - 0x%X], rax", offset);
    return SUCCESS;
}
