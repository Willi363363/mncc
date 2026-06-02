/*
** EPITECH PROJECT, 2026
** parser_run.c
** File description:
** Parser main execution function
*/
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/utils.h"

status_t parser_run(parser_t *parser)
{
    node_t *node = NULL;

    while (parser_peek(parser)->type != TOK_EOF) {
        node = parse_function(parser);
        if (!node)
            return EPARSE;
        if (array_push(parser->nodes, node) != SUCCESS) {
            node_destroy(node);
            return get_error(EPARSE, "function node implementation");
        }
    }
#ifdef MNCC_PARSER_DEBUG
    parser_print(parser);
#endif
    return SUCCESS;
}
