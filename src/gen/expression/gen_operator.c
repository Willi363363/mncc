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

static int gen_equal_operator(gen_t *gen, node_t *node)
{
    gen_expression(gen, node->right);
    gen->write(gen, "push rax");
    gen_expression(gen, node->left);
    gen->write(gen, "pop rbx");
    gen->write(gen, "cmp rax, rbx");
    gen->write(gen, "sete al");
    gen->write(gen, "movzx rax, al");
    return SUCCESS;
}

static int gen_div_operator(gen_t *gen, node_t *node)
{
    gen_expression(gen, node->right);
    gen->write(gen, "push rax");
    gen_expression(gen, node->left);
    gen->write(gen, "pop rbx");
    gen->write(gen, "xor rdx, rdx");
    gen->write(gen, "div rbx");
    return SUCCESS;
}

static int gen_basic_operator(gen_t *gen, node_t *node, char *str)
{
    gen_expression(gen, node->right);
    gen->write(gen, "push rax");
    gen_expression(gen, node->left);
    gen->write(gen, "pop rbx");
    if (node->op == OP_DIV) {
        gen->write(gen, "xor rdx, rdx");
        gen->write(gen, "div rbx");
        return SUCCESS;
    }
    gen->write(gen, "%s rax, rbx", str);
    return SUCCESS;
}

int gen_operator(gen_t *gen, node_t *node)
{
    switch (node->op) {
        case OP_ADD:
            return gen_basic_operator(gen, node, "add");
        case OP_SUB:
            return gen_basic_operator(gen, node, "sub");
        case OP_MUL:
            return gen_basic_operator(gen, node, "imul");
        case OP_DIV:
            return gen_div_operator(gen, node);
        case OP_EQUAL:
            return gen_equal_operator(gen, node);
        default:
            return get_error(EGEN,
                "unsupported operator type in expression: '%s'",
                node->name);
    }
}
