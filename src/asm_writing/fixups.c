/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** fixups
*/

#include "asm/asm.h"
#include <string.h>

status_t fixup_list_init(fixup_list_t **fl)
{
    if (!fl)
        return EELF;
    *fl = calloc(1, sizeof(fixup_list_t));
    return (*fl ? SUCCESS : EELF);
}

static fixup_t *fixup_list_alloc_slot(fixup_list_t **fl)
{
    size_t new_cap = 0;
    fixup_t *tmp = NULL;

    if (!fl || !*fl)
        return NULL;
    if ((*fl)->len >= (*fl)->cap) {
        new_cap = (*fl)->cap ? (*fl)->cap +
            FIXUP_DEFAULT_CAP : FIXUP_DEFAULT_CAP;
        tmp = realloc((*fl)->items, new_cap * sizeof(fixup_t));
        if (!tmp)
            return NULL;
        (*fl)->items = tmp;
        (*fl)->cap = new_cap;
    }
    return &(*fl)->items[(*fl)->len];
}

status_t fixup_list_add(fixup_list_t **fl,
    size_t patch_offset, const char *symbol)
{
    fixup_t *fx = NULL;

    if (!fl || !*fl || !symbol)
        return EELF;
    fx = fixup_list_alloc_slot(fl);
    if (!fx)
        return EELF;
    fx->patch_offset = patch_offset;
    strncpy(fx->symbol, symbol, sizeof(fx->symbol) - 1);
    fx->symbol[sizeof(fx->symbol) - 1] = '\0';
    (*fl)->len += 1;
    return SUCCESS;
}

status_t fixup_list_free(fixup_list_t **fl)
{
    if (!fl || !*fl)
        return EELF;
    free((*fl)->items);
    free(*fl);
    *fl = NULL;
    return SUCCESS;
}

status_t fixup_list_resolve(fixup_list_t *fl, symtab_t *st, code_buffer_t **cb)
{
    size_t target_offset = 0;
    int32_t rel32 = 0;

    if (!fl || !st || !cb || !*cb)
        return EELF;
    for (size_t i = 0; i < fl->len; i++) {
        if (!symtab_lookup(st, fl->items[i].symbol, &target_offset))
            return EELF;
        rel32 = (int32_t)(target_offset - (fl->items[i].patch_offset + 4));
        if (cb_patch_4(cb, fl->items[i].patch_offset, (uint32_t)rel32) == EELF)
            return EELF;
    }
    return SUCCESS;
}
