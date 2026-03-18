/*
** EPITECH PROJECT, 2026
** node.h
** File description:
** Parser node header file
*/
#ifndef NODE_H
    #define NODE_H
    #include "utils/array.h"
    #define OPERATOR_COUNT 4
    #define DATA_TYPE_COUNT 2


typedef enum data_type_e {
    DATA_INT,
    DATA_POINTER,
    DATA_INVALID
} data_type_t;

typedef enum operator_type_e {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_INVALID
} operator_type_t;

typedef enum node_type_e {
    // instructions
    NODE_FUNCTION,
    NODE_BLOCK,
    NODE_ASSIGN,
    NODE_DECLARATION,
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

    data_type_t data_type; // for VAR / FUNCTION
    char *name;         // for VAR / FUNCTION
    int value;          // for CONST
    operator_type_t op; // for OPERATOR

    array_t *childs;
} node_t;

node_t *node_create(node_type_t type);
void node_destroy(node_t *node);

#endif /* NODE_H */
