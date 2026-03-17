/*
** EPITECH PROJECT, 2026
** parser_moves.c
** File description:
** Parser token navigation and matching functions
*/
#include "parser/parser.h"

token_t *parser_peek(parser_t *p)
{
    if (p->cursor >= p->lexer->tokens->count)
        return NULL;
    return p->lexer->tokens->data[p->cursor];
}

token_t *parser_next(parser_t *p)
{
    token_t *tok = parser_peek(p);

    if (tok)
        p->cursor++;
    return tok;
}

bool parser_match(parser_t *p, token_type_t type)
{
    token_t *tok = parser_peek(p);

    if (tok && tok->type == type) {
        p->cursor++;
        return true;
    }
    return false;
}
