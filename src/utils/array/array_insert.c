/*
** EPITECH PROJECT, 2026
** array_insert.c
** File description:
** Insert an element in a dynamic array at a specific index
*/
#include <stdlib.h>
#include "main.h"
#include "utils/array.h"

status_t realloc_array(array_t *array)
{
    int new_capacity = array->capacity * 2;
    void **new_data = calloc(new_capacity, sizeof(void *));

    if (new_data == NULL)
        return EMEM;
    for (size_t i = 0; i < array->count; i++)
        new_data[i] = array->data[i];
    free(array->data);
    array->data = new_data;
    array->capacity = new_capacity;
    return SUCCESS;
}

status_t array_insert(array_t *array, size_t index, void *element)
{
    while (array->count + 1 >= array->capacity) {
        if (realloc_array(array) != SUCCESS)
            return EMEM;
    }
    for (size_t i = array->count; i > index; i--)
        array->data[i] = array->data[i - 1];
    array->data[index] = element;
    array->count++;
    return SUCCESS;
}
