/*
** EPITECH PROJECT, 2026
** gen_create.c
** File description:
** Generation context creation and initialization
*/
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gen/gen.h"
#include "parser/parser.h"
#include "utils/utils.h"

static void gen_write_function_va(gen_t *gen, const char *str, va_list args)
{
    for (int i = 0; i < gen->indentation; i++)
        fprintf(gen->out, "    ");
    vfprintf(gen->out, str, args);
    fputc('\n', gen->out);
}

static void gen_write_function(gen_t *gen, const char *str, ...)
{
    va_list args;

    va_start(args, str);
    gen_write_function_va(gen, str, args);
    va_end(args);
}

static void gen_add_section_function(gen_t *gen, const char *str, ...)
{
    char *comment = malloc(sizeof(char) * (strlen(str) + 4));
    va_list args;

    if (!comment) {
        get_error(ENOMEM, "code generation comment allocation");
        return;
    }
    va_start(args, str);
    fputc('\n', gen->out);
    sprintf(comment, "; %s", str);
    gen_write_function_va(gen, comment, args);
    va_end(args);
}

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
    gen->indentation = 0;
    gen->write = gen_write_function;
    gen->add_section = gen_add_section_function;
    if (!gen->out) {
        free(gen);
        return NULL;
    }
    gen->variables = NULL;
    return gen;
}
