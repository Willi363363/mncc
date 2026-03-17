/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** token_destroy
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
