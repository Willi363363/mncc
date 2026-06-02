/*
** EPITECH PROJECT, 2026
** lexer_extract_ident.c
** File description:
** Extraction of identifier tokens in the lexer with helper functions
*/
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lexer/extract.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "main.h"
#include "utils/utils.h"

static bool is_valid_char(char c, bool is_first)
{
    if (is_first)
        return isalpha(c) || c == '_';
    return isalnum(c) || c == '_';
}

status_t lexer_extract_ident(lexer_t *lexer)
{
    size_t start = 0;
    char *str = NULL;

    if (!lexer || !lexer->input ||
        !is_valid_char(lexer->input[lexer->pos], true))
        return ELEX;
    start = lexer->pos;
    for (; lexer->input[lexer->pos]; lexer->pos++)
        if (!is_valid_char(lexer->input[lexer->pos], false))
            break;
    str = strndup(lexer->input + start, lexer->pos - start);
    if (!str || lexer_push_token(lexer, TOK_IDENT, str) != SUCCESS)
        return get_error(ELEX, "lexer number token allocation");
    free(str);
    return SUCCESS;
}
