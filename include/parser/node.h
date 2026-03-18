/*
** EPITECH PROJECT, 2026
** node.h
** File description:
** Parser node header file
*/
#ifndef NODE_H
    #define NODE_H
    #include "utils/array.h"

typedef enum operator_type_e { OP_ADD, OP_SUB, OP_MUL, OP_DIV } operator_type_t;

typedef enum node_type_e {
    // instructions
    NODE_FUNCTION,
    NODE_BLOCK,
    NODE_ASSIGN,
    NODE_RETURN,

    // values
    NODE_CONST,
    NODE_VAR,
    NODE_OPERATOR,

    // both
    NODE_CALL
} node_type_t;

typedef struct node_s {
    node_type_t type;

    // for NODE_ASSIGN and NODE_OPERATOR
    struct node_s *left;
    struct node_s *right;

    char *name;         // for VAR / FUNCTION
    int value;          // for CONST
    operator_type_t op; // for OPERATOR

    array_t *childs;
} node_t;

node_t *node_create(node_type_t type);
void node_destroy(node_t *node);

#endif /* NODE_H */
