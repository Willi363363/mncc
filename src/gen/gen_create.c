/*
** EPITECH PROJECT, 2026
** gen_create.c
** File description:
** Generation context creation and initialization
*/
#include <errno.h>
#include <stdlib.h>
#include "gen/gen.h"
#include "utils/utils.h"

static FILE *open_file(const char *filename)
{
    FILE *out = fopen(filename, "w");

    if (!out) {
        get_error(ENOMEM, "code generation output file allocation");
        return NULL;
    }
    return out;
}

gen_t *gen_create(char *filename, parser_t *parser)
{
    gen_t *gen = malloc(sizeof(gen_t));

    if (!gen) {
        get_error(ENOMEM, "code generation context allocation");
        return NULL;
    }
    gen->parser = parser;
    gen->out = open_file(filename);
    if (!gen->out) {
        free(gen);
        return NULL;
    }
    gen->variables = NULL;
    return gen;
}
