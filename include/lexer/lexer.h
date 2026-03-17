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

#endif /* LEXER_H */
