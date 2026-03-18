/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** gen
*/

#ifndef GEN_H
    #define GEN_H
    #include <stdio.h>
    #include "parser/parser.h"
    #include "utils/array.h"

typedef struct stack_data_s {
    char *name;
    int offset;
} stack_data_t;

typedef struct stack_s {
    array_t *variables;
    struct stack_s *parent;
} stack_t;

typedef struct gen_s {
    parser_t *parser;
    FILE *out;
    stack_t *stack;
} gen_t;

gen_t *gen_create(char *filename, parser_t *parser);
int gen_run(gen_t *gen);
void gen_destroy(gen_t *gen);
int gen_header(gen_t *gen);
int gen_function(gen_t *gen, node_t *node);

// instruction generation
int gen_instruction(gen_t *gen, node_t *node);
int gen_declaration(gen_t *gen, node_t *node);
int gen_assignement(gen_t *gen, node_t *node);
int gen_return(gen_t *gen, node_t *node);
int gen_block(gen_t *gen, node_t *node);
int gen_call(gen_t *gen, node_t *node);

// expression generation
int gen_expression(gen_t *gen, node_t *node);
int gen_value(gen_t *gen, node_t *node);
int gen_operator(gen_t *gen, node_t *node);

#endif /* !GEN_H */
