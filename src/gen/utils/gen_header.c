/*
** EPITECH PROJECT, 2026
** gen_header.c
** File description:
** Generation of the header of the assembly file
*/

#include "gen/gen.h"
#include "main.h"

status_t gen_header(gen_t *gen)
{
    if (fprintf(gen->out, "section .text\n") < 0)
        return EGEN;
    if (fprintf(gen->out, "\t\tglobal _start\n\n") < 0)
        return EGEN;
    if (fprintf(gen->out, "_start:\n") < 0)
        return EGEN;
    if (fprintf(gen->out, "\t\tcall main\n") < 0)
        return EGEN;
    if (fprintf(gen->out, "\t\tmov rdi, rax\n") < 0)
        return EGEN;
    if (fprintf(gen->out, "\t\tmov rax, 60\n") < 0)
        return EGEN;
    if (fprintf(gen->out, "\t\tsyscall\n") < 0)
        return EGEN;
    return SUCCESS;
}
