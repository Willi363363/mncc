/*
** EPITECH PROJECT, 2026
** lexer_destroy.c
** File description:
** Destroys a lexer instance
*/
#include <stdlib.h>
#include "lexer/lexer.h"
#include "utils/array.h"

void lexer_destroy(lexer_t *lexer)
{
    if (!lexer)
        return;
    if (lexer->tokens)
        array_destroy(lexer->tokens, 1);
    if (lexer->input)
        free(lexer->input);
    free(lexer);
}
