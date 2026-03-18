/*
** EPITECH PROJECT, 2026
** gen_run.c
** File description:
** Generation of assembly code from parsed nodes
*/
#include "gen/gen.h"
#include "main.h"
#include "utils/utils.h"

int gen_run(gen_t *gen)
{
    node_t *node = NULL;

    if (gen_header(gen) != SUCCESS)
        return ERROR;
    fprintf(gen->out, "\n");
    for (int i = 0; i < gen->parser->nodes->count; i++) {
        node = gen->parser->nodes->data[i];
        if (node->type == NODE_FUNCTION && gen_function(gen, node) != SUCCESS)
            return ERROR;
        if (node->type != NODE_FUNCTION) {
            get_error(EGEN,
                "unsupported node type in global scope: '%s'",
                node->name);
            return ERROR;
        }
    }
    return SUCCESS;
}
