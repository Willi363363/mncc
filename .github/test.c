/*
** EPITECH PROJECT, 2026
** test.c
** File description:
** Test file for the MNCC project
*/

#include <stdio.h>

int get_ages_addition()
{
    int william = 18;
    int alessandro = 18;
    return william + alessandro;
}

int main()
{
    int factor = 0;
    int diff = 3;

    factor = 2;
    return diff + get_ages_addition() * factor;
}
