/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** gen_create
*/

#include "gen/gen.h"
#include <stdlib.h>

gen_t *gen_create(char *filename, parser_t *parser)
{
    gen_t *gen = malloc(sizeof(gen_t));

    if (!gen)
        return NULL;
    gen->parser = parser;
    gen->out = fopen(filename, "w");
    if (!gen->out) {
        free(gen);
        return NULL;
    }
    return gen;
}
