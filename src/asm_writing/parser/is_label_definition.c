/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** is_label_definition
*/

#include <string.h>
#include "asm/asm.h"

bool is_label_definition(const token_list_t *tl, char *out_name,
    size_t out_size)
{
    const char *tok;
    size_t len;
    size_t name_len;

    if (!tl || tl->count != 1)
        return false;
    tok = tl->items[0];
    len = strlen(tok);
    if (len < 2 || tok[len - 1] != ':')
        return false;
    name_len = len - 1;
    if (name_len >= out_size)
        name_len = out_size - 1;
    strncpy(out_name, tok, name_len);
    out_name[name_len] = '\0';
    return true;
}
