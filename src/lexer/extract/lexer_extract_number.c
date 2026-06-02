/*
** EPITECH PROJECT, 2026
** lexer_extract_number.c
** File description:
** Extraction of number tokens in the lexer with helper functions
*/
#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "lexer/extract.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "main.h"
#include "utils/utils.h"

status_t lexer_extract_number(lexer_t *lexer)
{
    size_t start = 0;
    char *str = NULL;

    if (!lexer || !lexer->input || !isdigit(lexer->input[lexer->pos]))
        return ELEX;
    start = lexer->pos;
    for (; lexer->input[lexer->pos]; lexer->pos++)
        if (!isdigit(lexer->input[lexer->pos]))
            break;
    str = strndup(lexer->input + start, lexer->pos - start);
    if (!str || lexer_push_token(lexer, TOK_NUMBER, str) != SUCCESS)
        return get_error(ELEX, "lexer number token allocation");
    free(str);
    return SUCCESS;
}
