/*
** EPITECH PROJECT, 2026
** lexer_extract_string.c
** File description:
** Extraction of string tokens in the lexer with helper functions
*/
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lexer/extract.h"
#include "lexer/lexer.h"
#include "main.h"
#include "utils/utils.h"

static status_t log_error(status_t type, void *ptr, char *message)
{
    free(ptr);
    return get_error(type, message);
}

status_t lexer_extract_string(lexer_t *lexer)
{
    size_t start = 0;
    char *str = NULL;

    if (!lexer || !lexer->input || lexer->input[lexer->pos] != STR_DELIM)
        return ELEX;
    lexer->pos++;
    start = lexer->pos;
    for (; lexer->input[lexer->pos]; lexer->pos++)
        if (lexer->input[lexer->pos] == STR_DELIM ||
            lexer->input[lexer->pos - 1] != '\\')
            break;
    if (lexer->input[lexer->pos] != STR_DELIM)
        return get_error(ELEX, "unterminated string literal");
    str = strndup(lexer->input + start, lexer->pos - start);
    if (!str || lexer_push_token(lexer, TOK_STR, str) != SUCCESS)
        return log_error(ELEX, str, "lexer string token allocation");
    free(str);
    lexer->pos++;
    return SUCCESS;
}
