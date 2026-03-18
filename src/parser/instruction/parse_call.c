/*
** EPITECH PROJECT, 2026
** parse_call.c
** File description:
** Call instruction parsing function with static helpers
*/
#include <errno.h>
#include <string.h>
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/utils.h"

static char *handle_call_name(parser_t *parser, node_t *node)
{
    char *name = NULL;

    if (!parser_match(parser, TOK_IDENT)) {
        node_destroy(node);
        get_error(EPAR,
            "expected function name identifier, got '%s'",
            parser_peek(parser)->value);
        return NULL;
    }
    name = strdup(parser_at(parser, parser->cursor - 1)->value);
    if (!name) {
        node_destroy(node);
        get_error(ENOMEM, "parser call name allocation");
        return NULL;
    }
    return name;
}

static bool handle_call_argument(parser_t *parser, node_t *node)
{
    node_t *arg = parse_expression(parser);

    if (!arg) {
        node_destroy(node);
        return false;
    }
    if (array_push(node->childs, arg) == ERROR) {
        node_destroy(arg);
        node_destroy(node);
        get_error(ENOMEM, "parser call argument implementation");
        return false;
    }
    return true;
}

static bool handle_call_arguments(parser_t *parser, node_t *node)
{
    if (!parser_match(parser, TOK_LPAREN)) {
        node_destroy(node);
        get_error(EPAR, "expected '(', got '%s'", parser_peek(parser)->value);
        return false;
    }
    while (parser_peek(parser)->type != TOK_RPAREN) {
        if (!handle_call_argument(parser, node)) {
            node_destroy(node);
            return false;
        }
        if (parser_peek(parser)->type == TOK_COMMA)
            parser_next(parser);
    }
    return true;
}

node_t *parse_call(parser_t *parser)
{
    node_t *node = node_create(NODE_CALL);

    if (!node) {
        get_error(ENOMEM, "parser call node allocation");
        return NULL;
    }
    node->name = handle_call_name(parser, node);
    if (!node->name)
        return NULL;
    if (!handle_call_arguments(parser, node))
        return NULL;
    return node;
}
