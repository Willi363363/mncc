/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** code_buffer_writes
*/

#include "asm/asm.h"

status_t cb_push_1(code_buffer_t **cb, unsigned char v)
{
    if (!cb || cb_adjust(cb, 1) == EELF)
        return EELF;
    (*cb)->ptr[(*cb)->len] = v;
    (*cb)->len += 1;
    return SUCCESS;
}

status_t cb_push_2(code_buffer_t **cb, u_int16_t v)
{
    unsigned char *dest = NULL;

    if (!cb || cb_adjust(cb, 2) == EELF)
        return EELF;
    dest = &((*cb)->ptr[(*cb)->len]);
    *(u_int16_t *)dest = v;
    (*cb)->len += 2;
    return SUCCESS;
}

status_t cb_push_4(code_buffer_t **cb, u_int32_t v)
{
    unsigned char *dest = NULL;

    if (!cb || cb_adjust(cb, 4) == EELF)
        return EELF;
    dest = &((*cb)->ptr[(*cb)->len]);
    *(u_int32_t *)dest = v;
    (*cb)->len += 4;
    return SUCCESS;
}

status_t cb_push_8(code_buffer_t **cb, uint64_t v)
{
    unsigned char *dest = NULL;

    if (!cb || cb_adjust(cb, 8) == EELF)
        return EELF;
    dest = &((*cb)->ptr[(*cb)->len]);
    *(uint64_t *)dest = v;
    (*cb)->len += 8;
    return SUCCESS;
}

status_t cb_patch_8(code_buffer_t **cb, size_t offset, uint64_t v)
{
    unsigned char *dest = NULL;
    if (!cb || !(*cb) || !(*cb)->ptr || (offset + 8) > (*cb)->len)
        return EELF;
    dest = &((*cb)->ptr[offset]);
    *(uint64_t *)dest = v;
    return SUCCESS;
}
