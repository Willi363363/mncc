/*
** EPITECH PROJECT, 2026
** gen_destroy.c
** File description:
** Generation context destruction and memory cleanup
*/
#include <stdlib.h>
#include "gen/gen.h"

void gen_destroy(gen_t *gen)
{
    if (!gen)
        return;
    if (gen->out)
        fclose(gen->out);
    free(gen);
}
