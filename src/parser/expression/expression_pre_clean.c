/*
** EPITECH PROJECT, 2026
** expression_pre_clean.c
** File description:
** Cleans up an expression by removing unnecessary parentheses before parsing
*/
#include "lexer/token.h"
#include "main.h"
#include "parser/parser.h"

status_t expression_pre_clean(parser_t *parser, size_t *size)
{
    token_t *first = parser_peek(parser);
    token_t *last = parser_at(parser, parser->cursor + *size - 1);

    while (first->type == TOK_LPAREN && last->type == TOK_RPAREN) {
        parser->cursor++;
        *size -= 2;
        first = parser_peek(parser);
        last = parser_at(parser, parser->cursor + *size - 1);
    }
    return SUCCESS;
}
