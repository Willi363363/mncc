/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** code_buffer utility file
*/

#include "asm/asm.h"

status_t cb_init(code_buffer_t **cb)
{
    if (!cb)
        return EELF;
    if (!(*cb))
        *cb = calloc(1, sizeof(code_buffer_t));
    if (!(*cb))
        return EELF;
    (*cb)->tot = CB_BUFFER_CAPACITY;
    (*cb)->len = 0;
    (*cb)->ptr = calloc(CB_BUFFER_CAPACITY, sizeof(unsigned char));
    return SUCCESS;
}

status_t cb_clear(code_buffer_t **cb)
{
    if (!cb || !(*cb) || !(*cb)->ptr)
        return EELF;
    for (size_t c = 0; c < (*cb)->len; c++)
        (*cb)->ptr[c] = 0;
    (*cb)->len = 0;
    return SUCCESS;
}

status_t cb_destroy(code_buffer_t **cb)
{
    if (!cb)
        return EELF;
    if (*cb) {
        free((*cb)->ptr);
        free(*cb);
    }
    (*cb) = NULL;
    return SUCCESS;
}

status_t cb_adjust(code_buffer_t **cb, size_t add_size)
{
    if (!cb || !(*cb) || !(*cb)->ptr)
        return EELF;
    if ((*cb)->len + add_size > (*cb)->tot) {
        while ((*cb)->tot < (*cb)->len + add_size)
            (*cb)->tot += CB_BUFFER_CAPACITY;
        (*cb)->ptr = realloc((*cb)->ptr, (*cb)->tot);
    }
    return SUCCESS;
}


status_t cb_pos(code_buffer_t *cb, size_t *len)
{
    if (!cb || !len)
        return EELF;
    *len = cb->len;
    return SUCCESS;
}