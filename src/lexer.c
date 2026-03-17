/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** lexer.c - Tokenizer for the MNC compiler
*/

#include "mncc.h"

token_type_t kw_type(char *text)
{
    if (strcmp(text, "int") == 0)
        return TOK_INT;
    if (strcmp(text, "return") == 0)
        return TOK_RETURN;
    if (strcmp(text, "if") == 0)
        return TOK_IF;
    if (strcmp(text, "else") == 0)
        return TOK_ELSE;
    if (strcmp(text, "while") == 0)
        return TOK_WHILE;
    return TOK_IDENT;
}

void lex_grow(lexer_t *lex)
{
    if (lex->count < lex->capacity)
        return;
    lex->capacity *= 2;
    lex->tokens = realloc(lex->tokens,
        sizeof(token_t) * lex->capacity);
    if (!lex->tokens) {
        fprintf(stderr, "Error: memory allocation failed\n");
        exit(84);
    }
}

void lex_add(lexer_t *lex, token_type_t type, char *text, int val)
{
    lex_grow(lex);
    lex->tokens[lex->count].type = type;
    lex->tokens[lex->count].text = strdup(text);
    lex->tokens[lex->count].value = val;
    lex->tokens[lex->count].line = lex->line;
    lex->count++;
}

void lex_word(lexer_t *lex)
{
    int start = lex->pos;
    char buf[256];
    int len = 0;
    token_type_t type;

    while (lex->src[lex->pos] &&
        (lex->src[lex->pos] == '_' ||
        (lex->src[lex->pos] >= 'a' && lex->src[lex->pos] <= 'z') ||
        (lex->src[lex->pos] >= 'A' && lex->src[lex->pos] <= 'Z') ||
        (lex->src[lex->pos] >= '0' && lex->src[lex->pos] <= '9'))) {
        buf[len++] = lex->src[lex->pos++];
    }
    buf[len] = '\0';
    (void)start;
    type = kw_type(buf);
    lex_add(lex, type, buf, 0);
}

void lex_number(lexer_t *lex)
{
    char buf[64];
    int len = 0;
    int val = 0;

    while (lex->src[lex->pos] >= '0' && lex->src[lex->pos] <= '9') {
        buf[len++] = lex->src[lex->pos++];
    }
    buf[len] = '\0';
    val = atoi(buf);
    lex_add(lex, TOK_NUMBER, buf, val);
}

token_t *tokenize(char *src, int *out_count)
{
    lexer_t lex;

    lex.src = src;
    lex.pos = 0;
    lex.line = 1;
    lex.capacity = 128;
    lex.count = 0;
    lex.tokens = xmalloc(sizeof(token_t) * lex.capacity);
    while (lex.src[lex.pos]) {
        skip_ws_comments(&lex);
        if (!lex.src[lex.pos])
            break;
        if (lex.src[lex.pos] == '_' ||
            (lex.src[lex.pos] >= 'a' && lex.src[lex.pos] <= 'z') ||
            (lex.src[lex.pos] >= 'A' && lex.src[lex.pos] <= 'Z'))
            lex_word(&lex);
        else if (lex.src[lex.pos] >= '0' && lex.src[lex.pos] <= '9')
            lex_number(&lex);
        else
            lex_op(&lex);
    }
    lex_add(&lex, TOK_EOF, "", 0);
    *out_count = lex.count;
    return lex.tokens;
}
