/*
** EPITECH PROJECT, 2026
** parse_assignment.c
** File description:
** Assignment instruction parsing function with static helpers
*/
#include <errno.h>
#include <string.h>
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/utils.h"

static node_t *handle_empty_declaration(parser_t *parser)
{
    node_t *node = node_create(NODE_DECLARATION);

    if (!node) {
        get_error(ENOMEM, "parser declaration node allocation");
        return NULL;
    }
    if (!parser_match(parser, TOK_IDENT)) {
        node_destroy(node);
        get_error(EPAR,
            "expected variable name identifier, got '%s'",
            parser_peek(parser)->value);
        return NULL;
    }
    node->name = strdup(parser_at(parser, parser->cursor - 1)->value);
    if (!node->name) {
        node_destroy(node);
        get_error(ENOMEM, "parser declaration name allocation");
        return NULL;
    }
    return node;
}

node_t *parse_declaration(parser_t *parser)
{
    data_type_t type = parse_data_type(parser);
    node_t *node = NULL;

    if (type == DATA_INVALID)
        return NULL;
    if (parser_at(parser, parser->cursor + 1)->type == TOK_EQ)
        node = parse_assignment(parser);
    else
        node = handle_empty_declaration(parser);
    if (!node)
        return NULL;
    node->type = NODE_DECLARATION;
    node->data_type = type;
    return node;
}
