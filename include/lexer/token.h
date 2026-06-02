/*
** EPITECH PROJECT, 2026
** lexer/token.h
** File description:
** Lexer token header file
*/

#ifndef TOKEN_H
    #define TOKEN_H

typedef enum token_type_e {
    // data types
    TOK_INT,

    // data literals
    TOK_NUMBER,
    TOK_STR,

    // keywords
    TOK_RETURN,
    TOK_IF,
    TOK_ELSE,
    TOK_WHILE,
    TOK_FOR,
    TOK_VOID,

    // identifiers and literals
    TOK_IDENT,

    // operators
    TOK_EQ,         // ==
    TOK_DEF,         // =
    TOK_PLUS,       // +
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
    TOK_EOF,
} token_type_t;

typedef struct token_s {
    token_type_t type;
    char *value;
} token_t;

token_t *token_create(token_type_t type, const char *value);
void token_destroy(token_t *token);

token_type_t get_keyword_type(const char *keyword);
token_type_t get_operator_type(char c);
token_type_t get_punctuation_type(char c);

#endif /* TOKEN_H */
