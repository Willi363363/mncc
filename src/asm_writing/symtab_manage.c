/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** symtab_manage
*/

#include "asm/asm.h"
#include <string.h>

status_t symtab_init(symtab_t **st)
{
    if (!st)
        return EELF;
    *st = calloc(1, sizeof(symtab_t));
    return (*st ? SUCCESS : EELF);
}

status_t symtab_free(symtab_t **st)
{
    if (!st)
        return EELF;
    if (*st)
        free((*st)->items);
    free(*st);
    *st = NULL;
    return SUCCESS;
}

static symbol_t *symtab_alloc_slot(symtab_t **st)
{
    symbol_t *new_items = NULL;
    size_t new_cap = 0;

    if (!st || !(*st))
        return NULL;
    if ((*st)->len >= (*st)->cap) {
        new_cap = (*st)->cap ? (*st)->cap +
            SYMTAB_DEFAULT_CAP : SYMTAB_DEFAULT_CAP;
        new_items = realloc((*st)->items, new_cap * sizeof(symbol_t));
        if (!new_items)
            return NULL;
        (*st)->items = new_items;
        (*st)->cap = new_cap;
    }
    return &(*st)->items[(*st)->len];
}

status_t symtab_define(symtab_t **st, const char *name, size_t offset)
{
    symbol_t *sym = NULL;

    if (!st || !*st || !name)
        return EELF;
    sym = symtab_alloc_slot(st);
    if (!sym)
        return EELF;
    strncpy(sym->name, name, sizeof(sym->name) - 1);
    sym->name[sizeof(sym->name) - 1] = '\0';
    sym->offset = offset;
    sym->defined = true;
    (*st)->len += 1;
    return SUCCESS;
}

bool symtab_lookup(symtab_t *st, const char *name, size_t *out_offset)
{
    if (!st || !name || !out_offset)
        return false;
    for (size_t i = 0; i < st->len; i++) {
        if (strcmp(st->items[i].name, name))
            continue;
        if (!st->items[i].defined)
            return false;
        *out_offset = st->items[i].offset;
        return true;
    }
    return false;
}
