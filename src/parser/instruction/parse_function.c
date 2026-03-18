/*
** EPITECH PROJECT, 2026
** parse_function.c
** File description:
** tokens parsing :
*/
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/array.h"
#include "utils/utils.h"

static int handle_data_type(parser_t *parser, node_t *node)
{
    node->data_type = parse_data_type(parser);
    if (node->data_type == DATA_INVALID) {
        node_destroy(node);
        get_error(EPAR, "expected a data type at the beginning of function");
        return EPAR;
    }
    return SUCCESS;
}

static int handle_function_name(parser_t *parser, node_t *node)
{
    if (!parser_match(parser, TOK_IDENT)) {
        node_destroy(node);
        get_error(EPAR,
            "expected function name identifier, got '%s'",
            parser_peek(parser)->value);
        return EPAR;
    }
    node->name = strdup(parser_peek(parser)->value);
    parser->cursor++;
    if (!node->name) {
        node_destroy(node);
        get_error(ENOMEM, "parser function name allocation");
        return ENOMEM;
    }
    return SUCCESS;
}

static node_t *handle_function_parameter(parser_t *parser, node_t *node)
{
    node_t *param = parse_declaration(parser);

    if (!param) {
        node_destroy(node);
        get_error(EPAR, "invalid function parameter declaration");
        return NULL;
    }
    if (array_push(node->childs, param) == ERROR) {
        node_destroy(param);
        node_destroy(node);
        get_error(ENOMEM, "parser function parameter implementation");
        return NULL;
    }
    return param;
}

static int handle_function_parameters(parser_t *parser, node_t *node)
{
    if (!parser_match(parser, TOK_LPAREN))
        return get_error(EPAR,
            "expected '(', got '%s'",
            parser_peek(parser)->value);
    parser->cursor++;
    while (!parser_match(parser, TOK_RPAREN)) {
        if (handle_function_parameter(parser, node) == NULL)
            return ERROR;
        if (parser_peek(parser)->type == TOK_RPAREN)
            break;
        if (!parser_match(parser, TOK_COMMA))
            return get_error(EPAR,
                "expected ',' or ')', got '%s'",
                parser_peek(parser)->value);
        parser->cursor++;
    }
    parser->cursor++;
    return SUCCESS;
}

static int handle_body(parser_t *parser, node_t *node)
{
    node_t *body = parse_block(parser);

    if (!body) {
        node_destroy(node);
        get_error(EPAR, "invalid function body");
        return ERROR;
    }
    if (array_push(node->childs, body) == ERROR) {
        node_destroy(body);
        node_destroy(node);
        get_error(ENOMEM, "parser function body implementation");
        return ERROR;
    }
    return SUCCESS;
}

node_t *parse_function(parser_t *parser)
{
    node_t *node = node_create(NODE_FUNCTION);

    if (!node) {
        get_error(ENOMEM, "parser function node allocation");
        return NULL;
    }
    if (handle_data_type(parser, node) != SUCCESS)
        return NULL;
    if (handle_function_name(parser, node) != SUCCESS)
        return NULL;
    if (handle_function_parameters(parser, node) != SUCCESS){
        node_destroy(node);
        return NULL;
    }
    if (handle_body(parser, node) != SUCCESS)
        return NULL;
    return node;
}
