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
    switch (code) {
        case EINP:
            fprintf(stderr, "Implementation error");
            break;
        case ELEX:
            fprintf(stderr, "Lexer error");
            break;
        case EPAR:
            fprintf(stderr, "Parser error");
            break;
        case EGEN:
            fprintf(stderr, "Generation error");
            break;
        default:
            return code;
    }
    if (message) {
        fprintf(stderr, ": %s\n", message);
    } else {
        fprintf(stderr, "\n");
    }
    if (detail)
        fprintf(stderr, "Details : %s\n", detail);
    return code;
}
