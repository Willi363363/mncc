/*
** EPITECH PROJECT, 2026
** parser_moves.c
** File description:
** Parser token navigation and matching functions
*/
#include "parser/parser.h"

token_t *parser_at(parser_t *p, int index)
{
    if (p->lexer->tokens->count <= index)
        return NULL;
    return p->lexer->tokens->data[index];
}

token_t *parser_peek(parser_t *p)
{
    return parser_at(p, p->cursor);
}

token_t *parser_next(parser_t *p)
{
    token_t *tok = parser_peek(p);

    if (tok)
        p->cursor++;
    return parser_peek(p);
}

bool parser_match(parser_t *p, token_type_t type)
{
    token_t *tok = parser_peek(p);

    return tok && tok->type == type;
}

token_t **parser_tokens_peek(parser_t *p)
{
    int index = p->cursor;

    if (p->lexer->tokens->count <= index)
        return NULL;
    return (token_t **)p->lexer->tokens->data + index;
}
