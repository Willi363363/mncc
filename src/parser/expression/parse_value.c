/*
** EPITECH PROJECT, 2026
** parse_value.c
** File description:
** Value expression parsing function
*/
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/array.h"
#include "utils/utils.h"

static node_t *create_const_node(token_t *token)
{
    node_t *node = node_create(NODE_CONST);

    if (!node) {
        get_error(ENOMEM, NULL, "parser const node allocation");
        return NULL;
    }
    node->value = atoi(token->value);
    return node;
}

static node_t *create_var_node(token_t *token)
{
    node_t *node = node_create(NODE_VAR);

    if (!node) {
        get_error(ENOMEM, NULL, "parser var node allocation");
        return NULL;
    }
    node->name = strdup(token->value);
    if (!node->name) {
        node_destroy(node);
        get_error(ENOMEM, NULL, "parser var name allocation");
        return NULL;
    }
    return node;
}

static node_t *get_value_node(parser_t *parser)
{
    token_t *token = parser_peek(parser);
    node_t *node = NULL;

    if (token->type == TOK_NUMBER)
        node = create_const_node(token);
    if (token->type == TOK_IDENT &&
        parser_at(parser, parser->cursor + 1)->type == TOK_LPAREN)
        node = parse_call(parser);
    else if (token->type == TOK_IDENT)
        node = create_var_node(token);
    if (!node) {
        get_error(EPAR,
            "expected a number or an identifier, got '%s'",
            token->value);
        return NULL;
    }
    return node;
}

node_t *parse_value(parser_t *parser)
{
    token_t *token = parser_peek(parser);
    node_t *node = NULL;

    if (!token) {
        get_error(EPAR,
            "expected a number or an identifier, but got end of input");
        return NULL;
    }
    node = get_value_node(parser);
    if (!node)
        return NULL;
    parser_next(parser);
    return node;
}
