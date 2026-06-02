/*
** EPITECH PROJECT, 2026
** lexer_push_token.c
** File description:
** Pushes a new token to the lexer's token array
*/
#include <stdlib.h>
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "main.h"

status_t lexer_push_token(lexer_t *lexer, token_type_t type, const char *value)
{
    token_t *token_struct = token_create(type, value);

    if (!token_struct)
        return ELEX;
    if (array_push(lexer->tokens, token_struct) != SUCCESS) {
        free(token_struct);
        return ELEX;
    }
    return SUCCESS;
}
