/*
** EPITECH PROJECT, 2026
** gen_destroy.c
** File description:
** Generation context destruction and memory cleanup
*/
#include <errno.h>
#include <stdlib.h>
#include "gen/gen.h"
#include "utils/array.h"

void gen_destroy(gen_t *gen)
{
    stack_t *stack = NULL;

    if (!gen)
        return;
    while (gen->stack) {
        if (gen->stack->variables)
            array_destroy(gen->stack->variables, 1);
        stack = gen->stack->parent;
        free(gen->stack);
        gen->stack = stack;
    }
    if (gen->out)
        fclose(gen->out);
    free(gen);
}
