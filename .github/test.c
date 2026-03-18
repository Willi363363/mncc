/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** test
*/

// this file is used to test the lexer and the tokenization of the input string

#include <stdio.h>
#include <stdlib.h>
#include "lexer/lexer.h"
#include "lexer/token.h"
#include "main.h"

int main()
{
    int a = 4;
    int b = 2;

    a = 8 + a + b - 4 * 2 / 2;
    return a;
}

// again a test file to test the lexer and the tokenization of the input string
