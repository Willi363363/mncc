/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** Creates a new token instance
*/

#include <stdlib.h>
#include "lexer/token.h"

void token_destroy(token_t *token)
{
    if (!token)
        return;
    free(token->value);
    free(token);
}
