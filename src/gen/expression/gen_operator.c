/*
** EPITECH PROJECT, 2026
** gen_operator.c
** File description:
** Generation of operator nodes to assembly code
*/
#include <stdio.h>
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"
#include "utils/utils.h"

static char *get_operator_str(operator_type_t op)
{
    switch (op) {
        case OP_ADD:
            return "add";
        case OP_SUB:
            return "sub";
        case OP_MUL:
            return "imul";
        case OP_DIV:
            return "idiv";
        default:
            return NULL;
    }
}

int gen_operator(gen_t *gen, node_t *node)
{
    char *op_str = get_operator_str(node->op);

    if (!op_str) {
        get_error(EGEN, "invalid operator in code generation");
        return ERROR;
    }
    gen_expression(gen, node->right);
    fprintf(gen->out, "    push rax\n");
    gen_expression(gen, node->left);
    fprintf(gen->out, "    pop rbx\n");
    if (node->op == OP_DIV) {
        fprintf(gen->out, "    xor rdx, rdx\n");
        fprintf(gen->out, "    div rbx\n");
        return SUCCESS;
    }
    fprintf(gen->out, "    %s rax, rbx\n", op_str);
    return SUCCESS;
}
