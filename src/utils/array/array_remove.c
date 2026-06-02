/*
** EPITECH PROJECT, 2026
** array_remove.c
** File description:
** Remove an element from a dynamic array at a specific index
*/
#include "main.h"
#include "utils/array.h"

status_t array_remove(array_t *array, size_t index)
{
    if (index >= array->count)
        return EMEM;
    for (size_t i = index; i < array->count - 1; i++)
        array->data[i] = array->data[i + 1];
    array->count--;
    array->data[array->count] = NULL;
    return SUCCESS;
}
