#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARRAY_CREATE_FUNCTION(name) ARRAY(name) create_##name##_array(void) \
{ \
    return NULL; \
}

#define ARRAY_DESTROY_FUNCTION(name) void destroy_##name##_array(ARRAY(name) arr) \
{ \
    while (arr) { \
        ARRAY(name) next = arr->next; \
        free(arr); \
        arr = next; \
    } \
}

#define ARRAY_FOREACH_FUNCTION(name) void foreach_##name##_array(ARRAY(name) arr, void (*f)(void *)) \
{ \
    while (arr) { \
        f(arr->data); \
        arr = arr->next; \
    } \
}

#define ARRAY_MAP_FUNCTION(name) void map_##name##_array(ARRAY(name) arr, void *(*f)(void *)) \
{ \
    while (arr) { \
        arr->data = f(arr->data); \
        arr = arr->next; \
    } \
}

#define ARRAY_APPEND_FUNCTION(name) int append_##name##_array(ARRAY(name) *arr, void *data) \
{ \
    ARRAY(name) new_node = malloc(sizeof(*new_node)); \
    if (!new_node) \
        return -1; \
    new_node->data = data; \
    new_node->next = NULL; \
\
    if (!*arr) { \
        *arr = new_node; \
        return 0; \
    } \
\
    ARRAY(name) current = *arr; \
    while (current->next) \
        current = current->next; \
    current->next = new_node; \
    return 0; \
}

#define DEFINE_ARRAY(T, name) typedef struct array_##name##_s { \
    T data;                                                     \
    struct array_##name##_s *next;                              \
} name##_t; \
    ARRAY_CREATE_FUNCTION(name) \
    ARRAY_DESTROY_FUNCTION(name) \
    ARRAY_APPEND_FUNCTION(name) \
    ARRAY_FOREACH_FUNCTION(name) \
    ARRAY_MAP_FUNCTION(name)

#define ARRAY(name) name##_t *

DEFINE_ARRAY(void *, generic);
DEFINE_ARRAY(char *, string);
DEFINE_ARRAY(int *, int);

typedef void (*print_func_t)(void *);

void print_string(void *data)
{
    char *str = (char *)data;
    
    str[0] = 'X'; // Modify the first character to demonstrate mutability
    printf("%s\n", (char *)str);
}

void print_number(void *data)
{
    printf("%d\n", *(int *)data);
}

void *increment_number(void *data)
{
    int *num = (int *)data;
    (*num) *= 2;
    return num;
}

int main(void)
{
    ARRAY(int) int_array = create_int_array();
    int v = 42;
    int x = 2;
    int y = -3;

    append_int_array(&int_array, &v);
    append_int_array(&int_array, &x);
    append_int_array(&int_array, &y);
    foreach_int_array(int_array, print_number);
    map_int_array(int_array, increment_number);
    printf("===\n");
    foreach_int_array(int_array, print_number);
    destroy_int_array(int_array);
    return 0;
}