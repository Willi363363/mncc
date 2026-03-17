/*
** EPITECH PROJECT, 2026
** lexer.h
** File description:
** Lexer header file
*/
#ifndef LEXER_H
    #define LEXER_H
    #include "array.h"

typedef struct lexer_s {
    array_t *tokens;
} lexer_t;

lexer_t *init_lexer(void);
void run_lexer(lexer_t *lexer, char const *src);

#endif /* LEXER_H */
