/*
** EPITECH PROJECT, 2026
** lexer_print.c
** File description:
** Prints the tokens of a lexer for debugging purposes
*/
#include <stdio.h>
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "main.h"
#include "utils/utils.h"

static const token_debug_t token_debug[] = {{TOK_EOF, "EOF"},
    {TOK_IDENT, "IDENT"},
    {TOK_NUMBER, "NUMBER"},
    {TOK_STR, "STRING"},
    {TOK_WHILE, "WHILE"},
    {TOK_IF, "IF"},
    {TOK_ELSE, "ELSE"},
    {TOK_FOR, "FOR"},
    {TOK_RETURN, "RETURN"},
    {TOK_INT, "INT"},
    {TOK_VOID, "VOID"},
    {TOK_SEMI, "SEMI"},
    {TOK_LPAREN, "LPAREN"},
    {TOK_RPAREN, "RPAREN"},
    {TOK_LBRACE, "LBRACE"},
    {TOK_RBRACE, "RBRACE"},
    {TOK_COMMA, "COMMA"},
    {TOK_EQ, "EQ"},
    {TOK_DEF, "DEF"},
    {TOK_PLUS, "PLUS"},
    {TOK_MINUS, "MINUS"},
    {TOK_MUL, "MUL"},
    {TOK_DIV, "DIV"}};

static token_debug_t *get_token_debug(token_type_t type)
{
    for (size_t i = 0; i < sizeof(token_debug) / sizeof(token_debug[0]); i++)
        if (token_debug[i].type == type)
            return (token_debug_t *)&token_debug[i];
    return NULL;
}

status_t lexer_print(lexer_t *lexer)
{
    token_t *tok = NULL;
    token_debug_t *debug = NULL;

    for (size_t i = 0; i < lexer->tokens->count; i++) {
        tok = lexer->tokens->data[i];
        debug = get_token_debug(tok->type);
        if (!debug)
            return get_error(EGEN, "unknown token type: %d", tok->type);
        printf("%s('%s') ", debug->name, tok->value ? tok->value : "");
    }
    fflush(stdout);
    return SUCCESS;
}
