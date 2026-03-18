#ifndef GEN_H
    #define GEN_H
    #include <stdio.h>
    #include "parser/parser.h"

typedef struct gen_s {
    parser_t *parser;
    FILE *out;
} gen_t;

gen_t *gen_create(char *filename, parser_t *parser);
void gen_destroy(gen_t *gen);
int gen_header(gen_t *gen);
int gen_function(gen_t *gen, node_t *node);
int gen_instruction(gen_t *gen, node_t *node);
int gen_expression(gen_t *gen, node_t *node);

#endif /* !GEN_H */
