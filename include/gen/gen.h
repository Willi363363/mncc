/*
** EPITECH PROJECT, 2026
** gen.h
** File description:
** Header file for the asm generation module
*/
#ifndef GEN_H
    #define GEN_H
    #include <stdio.h>
    #include "main.h"
    #include "parser/parser.h"
    #include "utils/array.h"

typedef struct variable_s {
    char *name;
    int offset;
} variable_t;

typedef struct gen_s {
    parser_t *parser;
    FILE *out;
    array_t *variables;
    int indentation;
    void (*write)(struct gen_s *gen, const char *str, ...);
    void (*add_section)(struct gen_s *gen, const char *str, ...);
} gen_t;

gen_t *gen_create(char *filename, parser_t *parser);
status_t gen_run(gen_t *gen);
status_t gen_header(gen_t *gen);
status_t gen_function(gen_t *gen, node_t *node);
void gen_destroy(gen_t *gen);

// instruction generation
status_t gen_instruction(gen_t *gen, node_t *node);
status_t gen_declaration(gen_t *gen, node_t *node);
status_t gen_assignement(gen_t *gen, node_t *node);
status_t gen_return(gen_t *gen, node_t *node);
status_t gen_block(gen_t *gen, node_t *node);
status_t gen_call(gen_t *gen, node_t *node);
status_t gen_if(gen_t *gen, node_t *node);

// expression generation
status_t gen_expression(gen_t *gen, node_t *node);
status_t gen_value_in_register(gen_t *gen, node_t *node, int i);
status_t gen_operator(gen_t *gen, node_t *node);

const char *gen_get_register(int i);
ssize_t gen_get_var_offset(gen_t *gen, const char *name);

#endif /* !GEN_H */
