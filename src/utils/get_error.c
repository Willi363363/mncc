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
    if (message)
        fprintf(stderr, "Input error :")
}

int get_error(int code, const char *message, const char *detail)
{
    switch (code) {
        case EINP:
        return ;
    
        default:
            return code;
    }
    return code;
}