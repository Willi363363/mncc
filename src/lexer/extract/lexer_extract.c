/*
** EPITECH PROJECT, 2026
** lexer_extract.c
** File description:
** Extract functions for the lexer
*/
#include <stddef.h>
#include "lexer/extract.h"
#include "main.h"

status_t lexer_extract(lexer_t *lexer)
{
    if (!lexer || !lexer->input)
        return ELEX;
    if (lexer_extract_fixed(lexer) == SUCCESS)
        return SUCCESS;
    if (lexer_extract_string(lexer) == SUCCESS)
        return SUCCESS;
    if (lexer_extract_number(lexer) == SUCCESS)
        return SUCCESS;
    if (lexer_extract_ident(lexer) == SUCCESS)
        return SUCCESS;
    return ELEX;
}
