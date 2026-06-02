/*
** EPITECH PROJECT, 2026
** utils/array.h
** File description:
** Dynamic array struct definition
*/

#ifndef ARRAY_H
    #define ARRAY_H
    #include <stdbool.h>
    #include <stddef.h>
    #include "main.h"
    #define ARRAY_INITIAL_CAPACITY (size_t)(4)

typedef void (*array_element_destroy_t)(void *element);

typedef struct array_s {
    size_t count;
    size_t capacity;
    void **data;
    array_element_destroy_t destroy_element;
} array_t;

array_t *array_create(array_element_destroy_t destroy_element);
status_t array_insert(array_t *array, size_t index, void *element);
status_t array_push(array_t *array, void *element);
status_t array_remove(array_t *array, size_t index);
status_t array_remove_element(array_t *array, void *element);
void array_destroy(array_t *array, bool destroy_elements);

#endif // ARRAY_H
