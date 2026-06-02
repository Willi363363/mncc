/*
** EPITECH PROJECT, 2026
** lexer_run.c
** File description:
** Run lexer tokenization
*/
#include "lexer/extract.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "main.h"

status_t lexer_run(lexer_t *lexer)
{
    if (!lexer || !lexer->input)
        return ELEX;
    while (lexer->input[lexer->pos]) {
        if (lexer_skip_ignored(lexer))
            continue;
        if (lexer_extract(lexer) != SUCCESS)
            return ELEX;
    }
    if (lexer_push_token(lexer, TOK_EOF, NULL) != SUCCESS)
        return ELEX;
#ifdef MNCC_LEXER_DEBUG
    lexer_print(lexer);
#endif
    return SUCCESS;
}
