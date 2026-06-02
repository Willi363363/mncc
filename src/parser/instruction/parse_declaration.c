/*
** EPITECH PROJECT, 2026
** parse_assignment.c
** File description:
** Assignment instruction parsing function with static helpers
*/
#include <stdio.h>
#include <string.h>
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/utils.h"

static node_t *handle_empty_declaration(parser_t *parser)
{
    node_t *node = node_create(NODE_DECLARATION);

    if (!node)
        return print_error(EMEM, "parser declaration node allocation");
    if (!parser_match(parser, TOK_IDENT)) {
        node_destroy(node);
        return print_error(
            EPARSE, "expected variable, got '%s'", parser_peek(parser)->value);
    }
    node->name = strdup(parser_peek(parser)->value);
    if (!node->name) {
        node_destroy(node);
        return print_error(EMEM, "parser declaration name allocation");
    }
    return node;
}

node_t *parse_declaration(parser_t *parser)
{
    data_type_t type = parse_data_type(parser);
    node_t *node = NULL;

    if (type == DATA_INVALID)
        return NULL;
    if (parser_at(parser, parser->cursor + 1)->type == TOK_DEF) {
        node = parse_assignment(parser);
        printf("Parsed assignement with name '%s'\n", node->left->name);
    } else {
        node = handle_empty_declaration(parser);
        parser->cursor++;
    }
    if (!node)
        return NULL;
    node->type = NODE_DECLARATION;
    node->data_type = type;
    return node;
}
