/*
** EPITECH PROJECT, 2026
** lexer_create.c
** File description:
** Creates a new lexer instance
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer/lexer.h"
#include "lexer/token.h"

lexer_t *lexer_create(void)
{
    lexer_t *lexer = malloc(sizeof(lexer_t));

    if (!lexer)
        return NULL;
    lexer->tokens = array_create((array_element_destroy_t)token_destroy);
    if (!lexer->tokens) {
        free(lexer);
        return NULL;
    }
    return lexer;
}
