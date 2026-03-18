/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** Tokenize char by char a string and return a list of tokens
*/

#include "lexer/lexer.h"
#include "main.h"
#include "lexer/token.h"
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

static token_type_t get_keyword_type(const char *keyword)
{
    if (strcmp(keyword, "if") == 0)
        return TOK_IF;
    if (strcmp(keyword, "else") == 0)
        return TOK_ELSE;
    if (strcmp(keyword, "while") == 0)
        return TOK_WHILE;
    if (strcmp(keyword, "for") == 0)
        return TOK_FOR;
    if (strcmp(keyword, "return") == 0)
        return TOK_RETURN;
    if (strcmp(keyword, "int") == 0)
        return TOK_INT;
    if (strcmp(keyword, "void") == 0)
        return TOK_VOID;
    return TOK_IDENT;
}

static token_type_t get_operator_type(char c)
{
    if (c == '=')
        return TOK_EQ;
    if (c == '+')
        return TOK_PLUS;
    if (c == '-')
        return TOK_MINUS;
    if (c == '*')
        return TOK_MUL;
    if (c == '/')
        return TOK_DIV;
    return TOK_EOF;
}

static token_type_t get_punctuation_type(char c)
{
    if (c == ';')
        return TOK_SEMI;
    if (c == '(')
        return TOK_LPAREN;
    if (c == ')')
        return TOK_RPAREN;
    if (c == '{')
        return TOK_LBRACE;
    if (c == '}')
        return TOK_RBRACE;
    if (c == ',')
        return TOK_COMMA;
    return TOK_EOF;
}

static int push_token(lexer_t *lexer, token_type_t type, const char *value)
{
    token_t *token_struct = token_create(type, value);

    if (!token_struct)
        return ERROR;
    if (array_push(lexer->tokens, token_struct) == ERROR) {
        free(token_struct);
        return ERROR;
    }
    return SUCCESS;
}

static int lexer_read_identifier(lexer_t *lexer, const char **input)
{
    const char *start = NULL;
    size_t len = 0;
    char *token = NULL;
    int result = 0;

    if (!lexer || !input || (!isalpha(**input) && **input != '_'))
        return ERROR;
    start = *input;
    while (isalnum(**input) || **input == '_')
        (*input)++;
    len = *input - start;
    token = strndup(start, len);
    if (!token)
        return ERROR;
    result = push_token(lexer, get_keyword_type(token), token);
    free(token);
    return result;
}

static int lexer_read_number(lexer_t *lexer, const char **input)
{
    const char *start = NULL;
    size_t len = 0;
    char *token = NULL;
    int result = 0;

    if (!lexer || !input || !isdigit(**input))
        return ERROR;
    start = *input;
    while (isdigit(**input))
        (*input)++;
    len = *input - start;
    token = strndup(start, len);
    if (!token)
        return ERROR;
    result = push_token(lexer, TOK_INT, token);
    free(token);
    return result;
}

static int lexer_read_symbol(lexer_t *lexer, const char **input,
    token_type_t type)
{
    char *token = NULL;
    int result = 0;

    if (type == TOK_EOF)
        return ERROR;
    token = strndup(*input, 1);
    if (!token)
        return ERROR;
    (*input)++;
    result = push_token(lexer, type, token);
    free(token);
    return result;
}

static int dispatch_token(lexer_t *lexer, const char **input)
{
    if (isalpha(**input) || **input == '_')
        return lexer_read_identifier(lexer, input);
    if (isdigit(**input))
        return lexer_read_number(lexer, input);
    if (strchr("=+-*/", **input))
        return lexer_read_symbol(lexer, input, get_operator_type(**input));
    if (strchr(";(){}.,", **input))
        return lexer_read_symbol(lexer, input, get_punctuation_type(**input));
    return ERROR;
}

int lexer_tokenize(lexer_t *lexer, const char *input)
{
    if (!lexer || !input)
        return ERROR;
    while (*input) {
        if (isspace(*input)) {
            input++;
            continue;
        }
        if (dispatch_token(lexer, &input) == ERROR)
            return ERROR;
    }
    return push_token(lexer, TOK_EOF, NULL);
}
