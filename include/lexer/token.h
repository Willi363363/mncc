/*
** EPITECH PROJECT, 2026
** token.h
** File description:
** Token structure definition
*/

#ifndef TOKEN_H
    #define TOKEN_H

typedef enum token_type_e {
    // data types
    TOK_INT,

    // keywords
    TOK_RETURN,

    // identifiers and literals
    TOK_IDENT,

    TOK_NUMBER,

    // operators
    TOK_EQ,         // =
    TOK_PLUS,       //e +
    TOK_MINUS,      // -
    TOK_MUL,        // *
    TOK_DIV,        // /

    // punctuation
    TOK_SEMI,       // ;
    TOK_LPAREN,     // (
    TOK_RPAREN,     // )
    TOK_LBRACE,     // {
    TOK_RBRACE,     // }
    TOK_COMMA,      // ,
    TOK_EOF
} token_type_t;

typedef struct token_s {
    token_type_t type;
    char *value;
} token_t;

token_t *token_create(token_type_t type, const char *value);
void token_destroy(token_t *token);

#endif /* TOKEN_H */
