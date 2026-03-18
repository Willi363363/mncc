/*
** EPITECH PROJECT, 2026
** parser.h
** File description:
** Parser header file
*/
#ifndef PARSER_H
    #define PARSER_H
    #include <stdbool.h>
    #include "lexer/lexer.h"
    #include "lexer/token.h"
    #include "parser/node.h"
    #include "utils/array.h"

typedef struct parser_s {
    lexer_t *lexer;
    int cursor;
    array_t *nodes;
} parser_t;

parser_t *parser_create(lexer_t *lexer);
int parser_run(parser_t *parser);
void parser_destroy(parser_t *parser);

data_type_t parse_data_type(parser_t *parser);

// moves
token_t *parser_at(parser_t *p, int index);
token_t *parser_peek(parser_t *p);
token_t *parser_next(parser_t *p);
bool parser_match(parser_t *p, token_type_t type);

// instruction
node_t *parse_instruction(parser_t *parser);
node_t *parse_sized_expression(parser_t *parser, int size);
node_t *parse_return(parser_t *parser);
node_t *parse_assignment(parser_t *parser);
node_t *parse_function(parser_t *parser);
node_t *parse_declaration(parser_t *parser);
node_t *parse_block(parser_t *parser);
node_t *parse_call(parser_t *parser);

// expression
node_t *parse_expression(parser_t *parser);
node_t *parse_operator(parser_t *parser, int size);
node_t *parse_value(parser_t *parser);

#endif /* PARSER_H */
