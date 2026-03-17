/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** Creates a new token instance
*/

#include "lexer/token.h"
#include <stdlib.h>
#include <string.h>

token_t *token_create(token_type_t type, const char *value)
{
    token_t *token = malloc(sizeof(token_t));

    if (!token)
        return NULL;
    token->type = type;
    token->value = value ? strdup(value) : NULL;
    return token;
}
