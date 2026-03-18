/*
** EPITECH PROJECT, 2026
** array.h
** File description:
** Dynamic array struct definition
*/

#ifndef ARRAY_H
    #define ARRAY_H
    #include <stddef.h>

typedef void (*array_element_destroy_t)(void *element);

typedef struct array_s {
    int count;
    int capacity;
    void **data;
    array_element_destroy_t destroy_element;
} array_t;

int format_array_index(array_t *array, int index, int allow_overflow);

array_t *array_create(array_element_destroy_t destroy_element);
int array_insert(array_t *array, int index, void *element);
int array_push(array_t *array, void *element);
int array_remove(array_t *array, int index);
int array_remove_element(array_t *array, void *element);
void array_destroy(array_t *array, int destroy_elements);

#endif // ARRAY_H
