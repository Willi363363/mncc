/*
** EPITECH PROJECT, 2026
** parse_function.c
** File description:
** Function instruction parsing function with static helpers
*/
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
        return get_error(
            EPARSE, "expected a data type at the beginning of function");
    }
    return SUCCESS;
}

static int handle_function_name(parser_t *parser, node_t *node)
{
    if (!parser_match(parser, TOK_IDENT)) {
        node_destroy(node);
        return get_error(EPARSE,
            "expected function name identifier, got '%s'",
            parser_peek(parser)->value);
    }
    node->name = strdup(parser_peek(parser)->value);
    parser->cursor++;
    if (!node->name) {
        node_destroy(node);
        return get_error(EMEM, "parser function name allocation");
    }
    return SUCCESS;
}

static node_t *handle_function_parameter(parser_t *parser, node_t *node)
{
    node_t *param = parse_declaration(parser);

    if (!param) {
        node_destroy(node);
        return print_error(EPARSE, "invalid function parameter declaration");
    }
    if (array_push(node->childs, param) == EPARSE) {
        node_destroy(param);
        node_destroy(node);
        return print_error(EMEM, "parser function parameter implementation");
    }
    return param;
}

static int handle_function_parameters(parser_t *parser, node_t *node)
{
    if (!parser_match(parser, TOK_LPAREN))
        return get_error(
            EPARSE, "expected '(', got '%s'", parser_peek(parser)->value);
    parser->cursor++;
    while (!parser_match(parser, TOK_RPAREN)) {
        if (handle_function_parameter(parser, node) == NULL)
            return EPARSE;
        if (parser_peek(parser)->type == TOK_RPAREN)
            break;
        if (!parser_match(parser, TOK_COMMA))
            return get_error(EPARSE,
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
        return get_error(EPARSE, "invalid function body");
    }
    if (array_push(node->childs, body) != SUCCESS) {
        node_destroy(body);
        node_destroy(node);
        return get_error(EMEM, "parser function body implementation");
    }
    return SUCCESS;
}

node_t *parse_function(parser_t *parser)
{
    node_t *node = node_create(NODE_FUNCTION);

    if (!node)
        return print_error(EMEM, "parser function node allocation");
    if (handle_data_type(parser, node) != SUCCESS)
        return NULL;
    if (handle_function_name(parser, node) != SUCCESS)
        return NULL;
    if (handle_function_parameters(parser, node) != SUCCESS) {
        node_destroy(node);
        return NULL;
    }
    if (handle_body(parser, node) != SUCCESS)
        return NULL;
    return node;
}
