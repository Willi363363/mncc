/*
** EPITECH PROJECT, 2026
** format_array_index.c
** File description:
** Format an index for a dynamic array
*/
#include "utils/array.h"

int format_array_index(array_t *array, int index, int allow_overflow)
{
    if (index < 0)
        index = array->count + index;
    if (index < 0 && !allow_overflow)
        index = 0;
    if (index > array->count && !allow_overflow)
        index = array->count;
    return index;
}
