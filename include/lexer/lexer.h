/*
** EPITECH PROJECT, 2026
** lexer.h
** File description:
** Lexer header file
*/
#ifndef LEXER_H
    #define LEXER_H
    #include <stdbool.h>
    #include <stddef.h>
    #include "lexer/token.h"
    #include "main.h"
    #include "utils/array.h"

    #define COMMENT_LINE "//"
    #define COMMENT_BLOCK_START "/*"
    #define COMMENT_BLOCK_END "*/"

typedef struct lexer_s {
    char *input;
    size_t pos;
    array_t *tokens;
} lexer_t;

typedef enum tok_category_type_e {
    TOK_CAT_KEYWORD,
    TOK_CAT_OPERATOR,
    TOK_CAT_PUNCTUATION,
    TOK_CAT_LITERAL
} tok_category_type_t;

typedef bool (*tok_char_validator_t)(char c);

typedef struct tok_category_s {
    tok_category_type_t type;
    tok_char_validator_t is_valid_char;
} tok_category_t;

typedef struct token_debug_s {
    token_type_t type;
    const char *name;
} token_debug_t;

lexer_t *lexer_create(const char *input);
status_t lexer_push_token(lexer_t *lexer, token_type_t type, const char *value);
bool lexer_skip_ignored(lexer_t *lexer);
status_t lexer_run(lexer_t *lexer);
status_t lexer_print(lexer_t *lexer);
void lexer_destroy(lexer_t *lexer);

#endif /* LEXER_H */
