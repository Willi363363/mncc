/*
** EPITECH PROJECT, 2026
** gen_value.c
** File description:
** Generation of value nodes to assembly code
*/
#include <stdio.h>
#include "gen/gen.h"
#include "main.h"
#include "parser/node.h"

static const char *REGISTERS[12] = {"rax",
    "rbx",
    "rcx",
    "rdx",
    "r8",
    "r9",
    "r10",
    "r11",
    "r12",
    "r13",
    "r14",
    "r15"};

static int load_arg_to_register(gen_t *gen, node_t *node, int i)
{
    const char *reg = REGISTERS[i];

    if (gen_expression(gen, node) != SUCCESS)
        return ERROR;
    fprintf(gen->out, "    mov %s, rax\n", reg);
    return SUCCESS;
}

static int load_arguments(gen_t *gen, node_t *node)
{
    for (int i = node->childs->count - 1; i >= 0; i--) {
        if (load_arg_to_register(gen, node->childs->data[i], i) != SUCCESS)
            return ERROR;
    }
    return SUCCESS;
}

int gen_call(gen_t *gen, node_t *node)
{
    for (int i = node->childs->count - 1; i >= 0; i--) {
        if (gen_expression(gen, node->childs->data[i]) != SUCCESS)
            return ERROR;
        fprintf(gen->out, "    push rax\n");
    }
    load_arguments(gen, node);
    fprintf(gen->out, "    call %s\n", node->name);
    fprintf(gen->out, "    add rsp, 0x%X\n", node->childs->count * 8);
    return SUCCESS;
}
