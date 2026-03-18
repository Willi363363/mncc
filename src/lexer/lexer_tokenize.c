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
    result = push_token(lexer, TOK_NUMBER, token);
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

static void skip_line_comment(const char **input)
{
    while (**input && **input != '\n')
        (*input)++;
    if (**input == '\n')
        (*input)++;
}

static void skip_block_comment(const char **input)
{
    while (**input && !(**input == '*' && *(*input + 1) == '/'))
        (*input)++;
    if (**input) {
        (*input) += 2;
    }
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
        if ((*input == '/' && *(input + 1) == '/') || *input == '#') {
            skip_line_comment(&input);
            continue;
        }
        if (*input == '/' && *(input + 1) == '*') {
            skip_block_comment(&input);
            continue;
        }
        if (dispatch_token(lexer, &input) == ERROR)
            return ERROR;
    }
    return push_token(lexer, TOK_EOF, NULL);
}
