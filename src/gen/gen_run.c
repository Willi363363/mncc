/*
** EPITECH PROJECT, 2026
** gen_run.c
** File description:
** Generation of assembly code from parsed nodes
*/
#include <stddef.h>
#include "gen/gen.h"
#include "main.h"
#include "utils/utils.h"

status_t gen_run(gen_t *gen)
{
    node_t *node = NULL;

    if (gen_header(gen) != SUCCESS)
        return EGEN;
    fprintf(gen->out, "\n");
    for (size_t i = 0; i < gen->parser->nodes->count; i++) {
        node = gen->parser->nodes->data[i];
        if (node->type == NODE_FUNCTION && gen_function(gen, node) != SUCCESS)
            return EGEN;
        if (node->type != NODE_FUNCTION)
            return get_error(EGEN,
                "unsupported node type in global scope: '%s'",
                node->name);
    }
    return SUCCESS;
}
