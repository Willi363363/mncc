/*
** EPITECH PROJECT, 2026
** gen_operator.c
** File description:
** Generation of operator nodes to assembly code
*/
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"
#include "utils/utils.h"

static void calculate_right_left(gen_t *gen, node_t *node)
{
    bool right_inline =
        node->right->type == NODE_CONST || node->right->type == NODE_VAR;

    if (!right_inline) {
        gen_expression(gen, node->right);
        gen->write(gen, "push %s", gen_get_register(0));
    }
    gen_expression(gen, node->left);
    if (right_inline)
        gen_value_in_register(gen, node->right, 1);
    else
        gen->write(gen, "pop %s", gen_get_register(1));
}

static int gen_equal_operator(gen_t *gen)
{
    gen->write(gen, "cmp rax, rbx");
    gen->write(gen, "sete al");
    gen->write(gen, "movzx rax, al");
    return SUCCESS;
}

static int gen_div_operator(gen_t *gen)
{
    gen->write(gen, "xor rdx, rdx");
    gen->write(gen, "div rbx");
    return SUCCESS;
}

static int gen_basic_operator(gen_t *gen, char *str)
{
    gen->write(gen, "%s rax, rbx", str);
    return SUCCESS;
}

int gen_operator(gen_t *gen, node_t *node)
{
    calculate_right_left(gen, node);
    switch (node->op) {
        case OP_ADD:
            return gen_basic_operator(gen, "add");
        case OP_SUB:
            return gen_basic_operator(gen, "sub");
        case OP_MUL:
            return gen_basic_operator(gen, "imul");
        case OP_DIV:
            return gen_div_operator(gen);
        case OP_EQUAL:
            return gen_equal_operator(gen);
        default:
            return get_error(EGEN,
                "unsupported operator type in expression: '%s'",
                node->name);
    }
}
