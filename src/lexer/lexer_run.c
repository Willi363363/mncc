/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** Run the lexer and print the tokens
*/

#include "main.h"
#include "utils/utils.h"
#include "lexer/token.h"
#include "lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>

static const char *get_keyword_token_str(token_type_t type)
{
    if (type == TOK_INT)
        return "TOK_INT";
    if (type == TOK_RETURN)
        return "TOK_RETURN";
    if (type == TOK_IF)
        return "TOK_IF";
    if (type == TOK_ELSE)
        return "TOK_ELSE";
    if (type == TOK_WHILE)
        return "TOK_WHILE";
    if (type == TOK_FOR)
        return "TOK_FOR";
    if (type == TOK_IDENT)
        return "TOK_IDENT";
    return NULL;
}

static const char *get_operator_token_str(token_type_t type)
{
    if (type == TOK_EQ)
        return "TOK_EQ";
    if (type == TOK_PLUS)
        return "TOK_PLUS";
    if (type == TOK_MINUS)
        return "TOK_MINUS";
    if (type == TOK_MUL)
        return "TOK_MUL";
    if (type == TOK_DIV)
        return "TOK_DIV";
    return NULL;
}

static const char *get_punctuation_token_str(token_type_t type)
{
    if (type == TOK_SEMI)
        return "TOK_SEMI";
    if (type == TOK_LPAREN)
        return "TOK_LPAREN";
    if (type == TOK_RPAREN)
        return "TOK_RPAREN";
    if (type == TOK_LBRACE)
        return "TOK_LBRACE";
    if (type == TOK_RBRACE)
        return "TOK_RBRACE";
    if (type == TOK_COMMA)
        return "TOK_COMMA";
    if (type == TOK_EOF)
        return "TOK_EOF";
    if (type == TOK_VOID)
        return "TOK_VOID";
    return "TOK_UNKNOWN";
}

static const char *get_token_type_str(token_type_t type)
{
    const char *str = get_keyword_token_str(type);

    if (!str)
        str = get_operator_token_str(type);
    if (!str)
        str = get_punctuation_token_str(type);
    return str;
}

static int print_lexer(lexer_t *lexer)
{
    token_t *token = NULL;

    for (int i = 0; i < lexer->tokens->count; i++) {
        token = (token_t *)lexer->tokens->data[i];
        printf("Token %d: Type=%s, Value='%s'\n", i,
            get_token_type_str(token->type), token->value ? token->value :
            "NULL");
    }
    return SUCCESS;
}

int lexer_run(char *buffer, lexer_t *lexer)
{
    if (lexer_tokenize(lexer, buffer) == ERROR) {
        free(buffer);
        return ERROR;
    }
    free(buffer);
    return print_lexer(lexer);
}
