/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** tokenize_line
*/

#include <string.h>
#include "asm/asm.h"

static size_t skip_separators(const char *line, size_t len, size_t i)
{
    while (i < len && (line[i] == ' ' || line[i] == '\t' ||
            line[i] == ','))
        i++;
    return i;
}

static size_t token_end(const char *line, size_t len, size_t start)
{
    size_t i = start;

    while (i < len && line[i] != ' ' && line[i] != '\t' &&
        line[i] != ',' && line[i] != ';')
        i++;
    return i;
}

static void store_token(token_list_t *out, const char *line, size_t start,
    size_t end)
{
    size_t tok_len = end - start;

    if (tok_len >= MAX_TOKEN_LEN)
        tok_len = MAX_TOKEN_LEN - 1;
    strncpy(out->items[out->count], &line[start], tok_len);
    out->items[out->count][tok_len] = '\0';
    out->count++;
}

status_t tokenize_line(const char *line, token_list_t *out)
{
    size_t i = 0;
    size_t len;
    size_t start;

    if (!line || !out)
        return EELF;
    len = strlen(line);
    out->count = 0;
    while (i < len && out->count < MAX_TOKENS) {
        i = skip_separators(line, len, i);
        if (i >= len || line[i] == ';')
            break;
        start = i;
        i = token_end(line, len, start);
        store_token(out, line, start, i);
    }
    return SUCCESS;
}
