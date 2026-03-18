/*
** EPITECH PROJECT, 2026
** lexer.h
** File description:
** Lexer header file
*/
#ifndef LEXER_H
    #define LEXER_H
    #include "utils/array.h"

typedef struct lexer_s {
    array_t *tokens;
} lexer_t;

lexer_t *lexer_create(void);
void lexer_destroy(lexer_t *lexer);
int lexer_tokenize(lexer_t *lexer, const char *input);
int lexer_run(char *buffer, lexer_t *lexer);



#endif /* LEXER_H */
