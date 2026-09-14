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
