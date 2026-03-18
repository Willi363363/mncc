/*
** EPITECH PROJECT, 2026
** array_remove.c
** File description:
** Remove an element from a dynamic array at a specific index
*/
#include "utils/array.h"
#include "main.h"

int array_remove(array_t *array, int index)
{
    index = format_array_index(array, index, 1);
    if (index < 0 || index >= array->count)
        return ERROR;
    for (int i = index; i < array->count - 1; i++)
        array->data[i] = array->data[i + 1];
    array->count--;
    array->data[array->count] = NULL;
    return SUCCESS;
}
