/*
** EPITECH PROJECT, 2026
** lexer/extract.h
** File description:
** Lexer token extraction functions header file
*/

#ifndef EXTRACT_H
    #define EXTRACT_H
    #include <stdbool.h>
    #include "lexer/lexer.h"
    #include "lexer/token.h"
    #include "main.h"

    #define STR_DELIM '"'

typedef bool (*tok_end_validator_t)(char c);

typedef struct tok_type_def_s {
    const char *str;
    token_type_t type;
    tok_end_validator_t is_valid_end;
} fixed_token_def_t;

bool any_end(char c);
bool is_keyword_end(char c);

status_t lexer_extract(lexer_t *lexer);
status_t lexer_extract_fixed(lexer_t *lexer);
status_t lexer_extract_number(lexer_t *lexer);
status_t lexer_extract_string(lexer_t *lexer);
status_t lexer_extract_ident(lexer_t *lexer);

#endif /* EXTRACT_H */
