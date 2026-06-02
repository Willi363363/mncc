/*
** EPITECH PROJECT, 2026
** lexer_extract_fixed.c
** File description:
** Extraction of fixed tokens in the lexer with helper functions
*/
#include <ctype.h>
#include <stddef.h>
#include <string.h>
#include "lexer/extract.h"
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "main.h"

static const fixed_token_def_t fixed_tokens[] = {
    {"while", TOK_WHILE, is_keyword_end},
    {"if", TOK_IF, is_keyword_end},
    {"else", TOK_ELSE, is_keyword_end},
    {"for", TOK_FOR, is_keyword_end},
    {"return", TOK_RETURN, is_keyword_end},
    {"int", TOK_INT, is_keyword_end},
    {"void", TOK_VOID, is_keyword_end},
    {";", TOK_SEMI, any_end},
    {"(", TOK_LPAREN, any_end},
    {")", TOK_RPAREN, any_end},
    {"{", TOK_LBRACE, any_end},
    {"}", TOK_RBRACE, any_end},
    {",", TOK_COMMA, any_end},
    {"==", TOK_EQ, any_end},
    {"=", TOK_DEF, any_end},
    {"+", TOK_PLUS, any_end},
    {"-", TOK_MINUS, any_end},
    {"*", TOK_MUL, any_end},
    {"/", TOK_DIV, any_end},
    {NULL, TOK_EOF, any_end}};

bool is_keyword_end(char c)
{
    return !isalnum(c) && c != '_';
}

bool any_end(char c)
{
    (void)c;
    return true;
}

size_t get_fixed_token_index(const char *str)
{
    size_t i = 0;
    const char *token_str = NULL;
    size_t len = 0;

    while (fixed_tokens[i].str) {
        token_str = fixed_tokens[i].str;
        len = strlen(token_str);
        if (strncmp(str, token_str, len) == 0 &&
            fixed_tokens[i].is_valid_end(str[len]))
            return i;
        i++;
    }
    return i;
}

status_t lexer_extract_fixed(lexer_t *lexer)
{
    const char *str = lexer->input + lexer->pos;
    size_t index = get_fixed_token_index(str);
    token_type_t type = fixed_tokens[index].type;

    if (type == TOK_EOF)
        return ELEX;
    lexer->pos += strlen(fixed_tokens[index].str);
    return lexer_push_token(lexer, type, fixed_tokens[index].str);
}
