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