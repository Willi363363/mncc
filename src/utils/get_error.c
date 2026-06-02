/*
** EPITECH PROJECT, 2026
** get_error.c
** File description:
** Print an error message to stderr based on the provided error code
*/
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include "main.h"
#include "utils/utils.h"

static void print_error_code(int code)
{
    switch (code) {
        case ELEX:
            fprintf(stderr, "Lexer error");
            break;
        case EPARSE:
            fprintf(stderr, "Parser error");
            break;
        case EGEN:
            fprintf(stderr, "Generation error");
            break;
        case EMEM:
            fprintf(stderr, "Memory error");
            break;
        default:
            errno = code;
            fprintf(stderr, "Error");
    }
}

static void print_error_vargs(status_t code, const char *message, va_list *args)
{
    print_error_code(code);
    fprintf(stderr, ": ");
    if (message && args)
        vfprintf(stderr, message, *args);
    fprintf(stderr, "\n");
    fflush(stderr);
}

status_t get_error(status_t code, const char *message, ...)
{
    va_list args;
    va_list *args_ptr = NULL;

    if (message) {
        va_start(args, message);
        args_ptr = &args;
    }
    print_error_vargs(code, message, args_ptr);
    if (message)
        va_end(args);
    return code;
}

void *print_error(status_t code, const char *message, ...)
{
    va_list args;
    va_list *args_ptr = NULL;

    if (message) {
        va_start(args, message);
        args_ptr = &args;
    }
    print_error_vargs(code, message, args_ptr);
    if (message)
        va_end(args);
    fprintf(stderr, "\n");
    return NULL;
}
