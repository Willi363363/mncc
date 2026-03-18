/*
** EPITECH PROJECT, 2026
** parser_run.c
** File description:
** Parser main execution function
*/
#include <errno.h>
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/utils.h"

int parser_run(parser_t *parser)
{
    node_t *node = NULL;

    while (parser_peek(parser)->type != TOK_EOF) {
        node = parse_function(parser);
        if (!node)
            return ERROR;
        if (array_push(parser->nodes, node) == ERROR) {
            node_destroy(node);
            get_error(ENOMEM, "parser function node implementation");
            return ERROR;
        }
    }
    return SUCCESS;
}
