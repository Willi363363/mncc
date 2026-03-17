/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** get_error.c
*/

#include "main.h"
#include <stdio.h>

static int print_EINP_error(const char *message, const char *detail)
{
    if (message) {
        fprintf(stderr, "Input error : %s\n", message);
    } else {
        fprintf(stderr, "Input error\n");
    }
    if (detail)
        fprintf(stderr, "Details : %s\n", detail);
    return EINP;
}

static int print_ELEX_error(const char *message, const char *detail)
{
    if (message) {
        fprintf(stderr, "Lexer error : %s\n", message);
    } else {
        fprintf(stderr, "Lexer error\n");
    }
    if (detail)
        fprintf(stderr, "Details : %s\n", detail);
    return ELEX;
}

static int print_EPAR_error(const char *message, const char *detail)
{
    if (message) {
        fprintf(stderr, "Parser error : %s\n", message);
    } else {
        fprintf(stderr, "Parser error\n");
    }
    if (detail)
        fprintf(stderr, "Details : %s\n", detail);
    return EPAR;
}

static int print_EGEN_error(const char *message, const char *detail)
{
    if (message) {
        fprintf(stderr, "Code generation error : %s\n", message);
    } else {
        fprintf(stderr, "Code generation error\n");
    }
    if (detail)
        fprintf(stderr, "Details : %s\n", detail);
    return EGEN;
}

int get_error(int code, const char *message, const char *detail)
{
    switch (code) {
        case EINP:
            return print_EINP_error(message, detail);
        case ELEX:
            return print_ELEX_error(message, detail);
        case EPAR:
            return print_EPAR_error(message, detail);
        case EGEN:
            return print_EGEN_error(message, detail);
        default:
            return code;
    }
}