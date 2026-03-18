/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** get_error.c
*/

#include "main.h"
#include <stdio.h>
#include <errno.h>
#include <stdarg.h>
#include <string.h>

static void print_error_code(int code)
{
    if (code < ELEX || code > EGEN) {
        errno = code;
        perror("Error");
    }
    if (code == EINP)
        fprintf(stderr, "Implementation error");
    if (code == ELEX)
        fprintf(stderr, "Lexer error");
    if (code == EPAR)
        fprintf(stderr, "Parser error");
    if (code == EGEN)
        fprintf(stderr, "Generation error");
}

int get_error(int code, const char *message, ...)
{
    va_list args;

    print_error_code(code);
    if (message && *message) {
        fprintf(stderr, (code < ELEX || code > EGEN) ? "At: " : ": ");
        va_start(args, message);
        vfprintf(stderr, message, args);
        va_end(args);
    }
    fprintf(stderr, "\n");
    return code;
}
