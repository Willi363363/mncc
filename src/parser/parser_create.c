/*
** EPITECH PROJECT, 2026
** parser_create
** File description:
** Parser creation and initialization
*/
#include <stdlib.h>
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/array.h"

parser_t *parser_create(lexer_t *lexer)
{
    parser_t *parser = malloc(sizeof(parser_t));

    if (!parser)
        return NULL;
    parser->lexer = lexer;
    parser->cursor = 0;
    parser->nodes = array_create((array_element_destroy_t)node_destroy);
    if (!parser->nodes) {
        free(parser);
        return NULL;
    }
    return parser;
}
