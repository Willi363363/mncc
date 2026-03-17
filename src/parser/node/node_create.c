/*
** EPITECH PROJECT, 2026
** node_create.c
** File description:
** Node creation and initialization
*/
#include <stdlib.h>
#include "utils/array.h"
#include "parser/node.h"

node_t *node_create(node_type_t type)
{
    node_t *node = malloc(sizeof(node_t));

    if (!node)
        return NULL;
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->name = NULL;
    node->value = 0;
    node->childs = array_create((array_element_destroy_t)node_destroy);
    if (!node->childs) {
        free(node);
        return NULL;
    }
    return node;
}
