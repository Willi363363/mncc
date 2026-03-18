/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** Run the lexer and print the tokens
*/

#include "main.h"
#include "utils/utils.h"
#include "lexer/token.h"
#include "lexer/lexer.h"
#include <stdio.h>
#include <stdlib.h>

int lexer_run(char *buffer, lexer_t *lexer)
{
    if (lexer_tokenize(lexer, buffer) == ERROR) {
        free(buffer);
        return ERROR;
    }
    free(buffer);
    return SUCCESS;
}
