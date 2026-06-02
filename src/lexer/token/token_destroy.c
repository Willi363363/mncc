/*
** EPITECH PROJECT, 2026
** token_destroy.c
** File description:
** Destruction of token instances and memory cleanup
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
