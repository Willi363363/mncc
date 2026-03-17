/*
** EPITECH PROJECT, 2026
** lexer.c
** File description:
** Lexer implementation - tokenizes a C source file into tokens
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lexer/lexer.h"
#include "lexer/token.h"

static void destroy_token(void *element)
{
    token_t *token = (token_t *)element;

    if (token == NULL)
        return;
    free(token->value);
    free(token);
}

static token_t *create_token(token_type_t type, char const *val)
{
    token_t *token = malloc(sizeof(token_t));

    if (token == NULL)
        return NULL;
    token->type = type;
    token->value = val ? strdup(val) : NULL;
    return token;
}

static token_type_t get_keyword_type(char const *word)
{
    if (strcmp(word, "int") == 0)
        return TOK_INT;
    if (strcmp(word, "return") == 0)
        return TOK_RETURN;
    return TOK_IDENT;
}

static void read_identifier(lexer_t *lexer, char const *src, int *i)
{
    int start = *i;
    char *word = NULL;
    token_type_t type;

    while (src[*i] && (isalnum(src[*i]) || src[*i] == '_'))
        (*i)++;
    word = strndup(src + start, *i - start);
    type = get_keyword_type(word);
    array_push(lexer->tokens, create_token(type, word));
    free(word);
}

static void read_number(lexer_t *lexer, char const *src, int *i)
{
    int start = *i;
    char *num = NULL;

    while (src[*i] && isdigit(src[*i]))
        (*i)++;
    num = strndup(src + start, *i - start);
    array_push(lexer->tokens, create_token(TOK_NUMBER, num));
    free(num);
}

static void read_operator(lexer_t *lexer, char const *src, int *i)
{
    char op[2] = {src[*i], '\0'};
    token_type_t type = TOK_EOF;

    switch (src[*i]) {
        case '+': type = TOK_PLUS; break;
        case '-': type = TOK_MINUS; break;
        case '*': type = TOK_MUL; break;
        case '/': type = TOK_DIV; break;
        case '=': type = TOK_EQ; break;
    }
    (*i)++;
    array_push(lexer->tokens, create_token(type, op));
}

static void read_punctuation(lexer_t *lexer, char const *src, int *i)
{
    char punct[2] = {src[*i], '\0'};
    token_type_t type = TOK_EOF;

    switch (src[*i]) {
        case ';': type = TOK_SEMI; break;
        case '(': type = TOK_LPAREN; break;
        case ')': type = TOK_RPAREN; break;
        case '{': type = TOK_LBRACE; break;
        case '}': type = TOK_RBRACE; break;
        case ',': type = TOK_COMMA; break;
    }
    (*i)++;
    array_push(lexer->tokens, create_token(type, punct));
}

static void dispatch_token(lexer_t *lexer, char const *src, int *i)
{
    if (isalpha(src[*i]) || src[*i] == '_') {
        read_identifier(lexer, src, i);
        return;
    }
    if (isdigit(src[*i])) {
        read_number(lexer, src, i);
        return;
    }
    if (strchr("+-*/=", src[*i])) {
        read_operator(lexer, src, i);
        return;
    }
    if (strchr(";(){},", src[*i])) {
        read_punctuation(lexer, src, i);
        return;
    }
    (*i)++;
}

void run_lexer(lexer_t *lexer, char const *src)
{
    int i = 0;

    if (lexer == NULL || src == NULL)
        return;
    while (src[i] != '\0') {
        while (src[i] && isspace(src[i]))
            i++;
        if (src[i] != '\0')
            dispatch_token(lexer, src, &i);
    }
    array_push(lexer->tokens, create_token(TOK_EOF, NULL));
}

lexer_t *init_lexer(void)
{
    lexer_t *lexer = malloc(sizeof(lexer_t));

    if (lexer == NULL)
        return NULL;
    lexer->tokens = array_create(destroy_token);
    return lexer;
}
