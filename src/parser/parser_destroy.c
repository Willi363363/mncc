/*
** EPITECH PROJECT, 2026
** parser_destroy.c
** File description:
** Parser destruction and memory cleanup
*/
#include <stdlib.h>
#include "parser/parser.h"

void parser_destroy(parser_t *parser)
{
    if (!parser)
        return;
    if (parser->nodes)
        array_destroy(parser->nodes, 1);
    free(parser);
}
