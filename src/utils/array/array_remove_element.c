/*
** EPITECH PROJECT, 2026
** array_remove_element.c
** File description:
** Remove an element from a dynamic array
*/
#include <fcntl.h>
#include <stdio.h>
#include "main.h"
#include "utils/array.h"

static ssize_t element_to_index(array_t *array, void *element)
{
    for (size_t i = 0; i < array->count; i++) {
        if (array->data[i] == element)
            return i;
    }
    return NOIDX;
}

status_t array_remove_element(array_t *array, void *element)
{
    ssize_t index = element_to_index(array, element);

    if (index == NOIDX)
        return EMEM;
    return array_remove(array, index);
}
