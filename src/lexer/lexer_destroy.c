/*
** EPITECH PROJECT, 2026
** mncc
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
    array_destroy(lexer->tokens, 1);
    free(lexer);
}
