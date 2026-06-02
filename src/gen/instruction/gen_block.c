/*
** EPITECH PROJECT, 2026
** gen_block.c
** File description:
** Generation of block instruction node to assembly code
*/
#include <stddef.h>
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"

status_t gen_block(gen_t *gen, node_t *node)
{
    for (size_t i = 0; i < node->childs->count; i++) {
        if (gen_instruction(gen, node->childs->data[i]) != SUCCESS)
            return EGEN;
    }
    return SUCCESS;
}
