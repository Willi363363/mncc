/*
** EPITECH PROJECT, 2026
** parser.h
** File description:
** Parser header file
*/
#ifndef PARSER_H
    #define PARSER_H
    #include "lexer/lexer.h"
    #include "utils/array.h"

typedef struct parser_s {
    lexer_t *lexer;
    int cursor;
    array_t *nodes;
} parser_t;

parser_t *parser_create(lexer_t *lexer);
int parser_run(parser_t *parser);
void parser_destroy(parser_t *parser);

#endif /* PARSER_H */
