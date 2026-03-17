/*
** EPITECH PROJECT, 2026
** array_remove_element.c
** File description:
** Remove an element from a dynamic array
*/
#include "array.h"
#include "main.h"

static int element_to_index(array_t *array, void *element)
{
    for (int i = 0; i < array->count; i++) {
        if (array->data[i] == element)
            return i;
    }
    return -1;
}

int array_remove_element(array_t *array, void *element)
{
    int index = element_to_index(array, element);

    if (index == -1)
        return ERROR;
    return array_remove(array, index);
}
