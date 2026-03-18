/*
** EPITECH PROJECT, 2026
** array_push.c
** File description:
** Push an element to the end of a dynamic array
*/
#include "utils/array.h"

int array_push(array_t *array, void *element)
{
    return array_insert(array, array->count, element);
}
