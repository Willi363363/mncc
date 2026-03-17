/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** get_error.c
*/

#include "main.h"
#include <stdio.h>

int get_error(int code, const char *message, const char *detail)
{
    if (code < ELEX || code > EGEN)
        return code;
    if (code == EINP)
        fprintf(stderr, "Implementation error");
    if (code == ELEX)
        fprintf(stderr, "Lexer error");
    if (code == EPAR)
        fprintf(stderr, "Parser error");
    if (code == EGEN)
        fprintf(stderr, "Generation error");
    if (message) {
        fprintf(stderr, ": %s\n", message);
    } else {
        fprintf(stderr, "\n");
    }
    if (detail)
        fprintf(stderr, "Details : %s\n", detail);
    return code;
}
