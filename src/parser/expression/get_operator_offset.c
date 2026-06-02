/*
** EPITECH PROJECT, 2026
** get_operator_offset.c
** File description:
** Get the offset of the operator with the lowest precedence in an expression
*/
#include "lexer/token.h"
#include "parser/parser.h"

ssize_t get_operator_offset(parser_t *parser, size_t size)
{
    size_t cursor = parser->cursor;
    token_t *token = NULL;
    size_t depth = 0;
    ssize_t offset = NOIDX;
    operator_type_t op = OP_NONE;

    for (size_t i = 0; i < size; i++) {
        token = parser_peek(parser);
        if (token->type == TOK_LPAREN)
            depth++;
        if (token->type == TOK_RPAREN)
            depth--;
        if (token_to_operator(token) < op && depth == 0) {
            offset = i;
            op = token_to_operator(token);
        }
        parser_next(parser);
    }
    parser->cursor = cursor;
    return offset;
}
