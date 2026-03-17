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
    #include "utils/array.h"

typedef struct parser_s {
    lexer_t *lexer;
    int cursor;
    array_t *nodes;
} parser_t;

parser_t *parser_create(lexer_t *lexer);
int parser_run(parser_t *parser);
void parser_destroy(parser_t *parser);

// moves
token_t *parser_peek(parser_t *p);
token_t *parser_next(parser_t *p);
bool parser_match(parser_t *p, token_type_t type);

#endif /* PARSER_H */
