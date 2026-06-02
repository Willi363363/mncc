/*
** EPITECH PROJECT, 2026
** parser.h
** File description:
** Parser header file
*/
#ifndef PARSER_H
    #define PARSER_H
    #include <stdbool.h>
    #include <stddef.h>
    #include <stdio.h>
    #include "lexer/lexer.h"
    #include "lexer/token.h"
    #include "parser/node.h"
    #include "utils/array.h"

typedef struct parser_s {
    lexer_t *lexer;
    size_t cursor;
    array_t *nodes;
    size_t id_counter;
} parser_t;

parser_t *parser_create(lexer_t *lexer);
status_t parser_run(parser_t *parser);
void parser_destroy(parser_t *parser);

data_type_t parse_data_type(parser_t *parser);

// moves
token_t *parser_at(parser_t *p, size_t index);
token_t *parser_peek(parser_t *p);
token_t *parser_next(parser_t *p);
bool parser_match(parser_t *p, token_type_t type);
token_t **parser_tokens_peek(parser_t *p);

// instruction
node_t *parse_instruction(parser_t *parser);
node_t *parse_expression_with_size(parser_t *parser, size_t size);
node_t *parse_return(parser_t *parser);
node_t *parse_assignment(parser_t *parser);
node_t *parse_function(parser_t *parser);
node_t *parse_declaration(parser_t *parser);
node_t *parse_block(parser_t *parser);
node_t *parse_call(parser_t *parser);
node_t *parse_if(parser_t *parser);

// expression
node_t *parse_expression(parser_t *parser);
node_t *parse_expression_with_size(parser_t *parser, size_t size);
node_t *parse_expression_with_operator(parser_t *parser, size_t size);
node_t *parse_value(parser_t *parser);
ssize_t get_expression_size(parser_t *parser);
status_t expression_pre_clean(parser_t *parser, size_t *size);
ssize_t get_operator_offset(parser_t *parser, size_t size);

// operator matching
bool is_operator_token(token_t *token);
token_type_t operator_to_token(operator_type_t op);
operator_type_t token_to_operator(token_t *token);

// debug
void parser_print(parser_t *parser);

#endif /* PARSER_H */
