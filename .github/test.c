/*
** EPITECH PROJECT, 2026
** test.c
** File description:
** Test file for the MNCC project
*/
#include <stdio.h>

int add(int a, int b)
{
    if (a == b)
        return a + 3;
    return b;
}

int main()
{
    return add(42, 42);
}
