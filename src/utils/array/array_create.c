/*
** EPITECH PROJECT, 2026
** array_create.c
** File description:
** Create a dynamic array
*/
#include <stdlib.h>
#include "utils/array.h"

array_t *array_create(array_element_destroy_t destroy_element)
{
    array_t *array = malloc(sizeof(array_t));

    if (array == NULL)
        return NULL;
    array->destroy_element = destroy_element;
    array->count = 0;
    array->capacity = 4;
    array->data = malloc(sizeof(void *) * array->capacity);
    if (array->data == NULL) {
        free(array);
        return NULL;
    }
    for (int i = 0; i < array->capacity; i++)
        array->data[i] = NULL;
    return array;
}
