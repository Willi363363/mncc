/*
** EPITECH PROJECT, 2026
** array_destroy.c
** File description:
** Function to destroy an array and free its resources
*/
#include <stdbool.h>
#include <stdlib.h>
#include "utils/array.h"

void array_destroy(array_t *array, bool destroy_elements)
{
    if (array == NULL)
        return;
    if (destroy_elements && array->destroy_element)
        for (size_t i = 0; destroy_elements && i < array->count; i++)
            array->destroy_element(array->data[i]);
    free(array->data);
    free(array);
}
