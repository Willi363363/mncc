/*
** EPITECH PROJECT, 2026
** array_insert.c
** File description:
** Insert an element in a dynamic array at a specific index
*/
#include <stdlib.h>
#include "array.h"
#include "main.h"

int realloc_array(array_t *array)
{
    int new_capacity = array->capacity * 2;
    void **new_data = malloc(sizeof(void *) * new_capacity);

    if (new_data == NULL)
        return ERROR;
    for (int i = 0; i < array->count; i++)
        new_data[i] = array->data[i];
    for (int i = array->count; i < new_capacity; i++)
        new_data[i] = NULL;
    free(array->data);
    array->data = new_data;
    array->capacity = new_capacity;
    return SUCCESS;
}

int array_insert(array_t *array, int index, void *element)
{
    index = format_array_index(array, index, 0);
    while (array->count + 1 >= array->capacity) {
        if (realloc_array(array) == ERROR)
            return ERROR;
    }
    for (int i = array->count; i > index; i--)
        array->data[i] = array->data[i - 1];
    array->data[index] = element;
    array->count++;
    return SUCCESS;
}
