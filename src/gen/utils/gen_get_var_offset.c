/*
** EPITECH PROJECT, 2026
** gen_get_var_offset.c
** File description:
** Get the offset of a variable in the stack
*/
#include <string.h>
#include "gen/gen.h"
#include "main.h"
#include "utils/utils.h"

ssize_t gen_get_var_offset(gen_t *gen, const char *name)
{
    variable_t *data = NULL;

    for (size_t i = 0; i < gen->variables->count; i++) {
        data = gen->variables->data[i];
        if (strcmp(data->name, name) == 0)
            return data->offset;
    }
    print_error(EGEN, "variable '%s' not found in stack", name);
    return NOIDX;
}
