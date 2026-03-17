/*
** EPITECH PROJECT, 2026
** node_destroy.c
** File description:
** Node destruction and memory cleanup
*/
#include <stdlib.h>
#include "parser/node.h"

void node_destroy(node_t *node)
{
    if (!node)
        return;
    if (node->name)
        free(node->name);
    if (node->left)
        node_destroy(node->left);
    if (node->right)
        node_destroy(node->right);
    if (node->childs)
        array_destroy(node->childs, 1);
    free(node);
}
