/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** gen_destroy
*/

#include "gen/gen.h"
#include <stdlib.h>

void gen_destroy(gen_t *gen)
{
    if (!gen)
        return;
    if (gen->out)
        fclose(gen->out);
    free(gen);
}
