/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** gen_header
*/

#include "gen/gen.h"
#include "main.h"

int gen_header(gen_t *gen)
{
    if (fprintf(gen->out, "section .text\n") < 0)
        return ERROR;
    if (fprintf(gen->out, "\t\tglobal _start\n\n") < 0)
        return ERROR;
    if (fprintf(gen->out, "_start:\n") < 0)
        return ERROR;
    if (fprintf(gen->out, "\t\tcall main\n") < 0)
        return ERROR;
    if (fprintf(gen->out, "\t\tmov rdi, rax\n") < 0)
        return ERROR;
    if (fprintf(gen->out, "\t\tmov rax, 60\n") < 0)
        return ERROR;
    if (fprintf(gen->out, "\t\tsyscall\n") < 0)
        return ERROR;
    return SUCCESS;
}
