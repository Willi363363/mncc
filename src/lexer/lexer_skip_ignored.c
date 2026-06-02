/*
** EPITECH PROJECT, 2026
** lexer_skip_ignored.c
** File description:
** Skips ignored characters in the lexer's input
*/
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "lexer/lexer.h"

static bool skip_line_comment(lexer_t *lexer)
{
    size_t len = strlen(COMMENT_LINE);

    if (strncmp(lexer->input + lexer->pos, COMMENT_LINE, len) != 0)
        return false;
    while (lexer->input[lexer->pos] && lexer->input[lexer->pos] != '\n')
        lexer->pos++;
    if (lexer->input[lexer->pos] == '\n')
        lexer->pos++;
    return true;
}

static bool skip_block_comment(lexer_t *lexer)
{
    size_t len_start = strlen(COMMENT_BLOCK_START);
    size_t len_end = strlen(COMMENT_BLOCK_END);

    if (strncmp(lexer->input + lexer->pos, COMMENT_BLOCK_START, len_start) != 0)
        return false;
    while (lexer->input[lexer->pos] &&
        strncmp(lexer->input + lexer->pos,
            COMMENT_BLOCK_END,
            strlen(COMMENT_BLOCK_END)) != 0)
        lexer->pos++;
    if (lexer->input[lexer->pos])
        lexer->pos += len_end;
    return true;
}

bool lexer_skip_ignored(lexer_t *lexer)
{
    if (!lexer)
        return false;
    if (isspace(lexer->input[lexer->pos])) {
        lexer->pos++;
        return true;
    }
    if (skip_line_comment(lexer))
        return true;
    if (skip_block_comment(lexer))
        return true;
    return false;
}
