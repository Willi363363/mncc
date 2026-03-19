/*
** EPITECH PROJECT, 2026
** parse_if.c
** File description:
** If instruction parsing function
*/
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/array.h"
#include "utils/utils.h"

static int extract_if_expression(parser_t *parser, node_t *if_node)
{
    node_t *expr = NULL;

    if (!parser_match(parser, TOK_LPAREN)) {
        get_error(EPAR, "expected '(' after 'if'");
        return ERROR;
    }
    parser->cursor++;
    expr = parse_expression(parser);
    if (!expr) {
        get_error(EPAR, "invalid expression in 'if' statement");
        return ERROR;
    }
    if (!parser_match(parser, TOK_RPAREN)) {
        node_destroy(expr);
        get_error(EPAR, "expected ')' after 'if' condition");
        return ERROR;
    }
    parser->cursor++;
    array_push(if_node->childs, expr);
    return SUCCESS;
}

static int extract_if_body(parser_t *parser, node_t *if_node)
{
    node_t *body = NULL;

    body = parse_block(parser);
    if (!body) {
        get_error(EPAR, "invalid block in 'if' statement");
        return ERROR;
    }
    array_push(if_node->childs, body);
    return SUCCESS;
}

static char *get_name(parser_t *parser)
{
    int id = parser->id_counter;
    char *name = malloc(sizeof(char) * 20);

    if (!name) {
        get_error(ENOMEM, "parser 'if' node name allocation");
        return NULL;
    }
    sprintf(name, "if_%d", id);
    parser->id_counter++;
    return name;
}

static int init_if_block(parser_t *parser, node_t *node)
{
    if (parser_next(parser)->type != TOK_LPAREN) {
        node_destroy(node);
        return get_error(EPAR,
            "expected '(' after 'if', got '%s'",
            parser_peek(parser) ? parser_peek(parser)->value : "end of input");
    }
    node->name = get_name(parser);
    if (!node->name) {
        node_destroy(node);
        return ERROR;
    }
    return SUCCESS;
}

node_t *parse_if(parser_t *parser)
{
    node_t *node = node_create(NODE_IF);

    if (!node || init_if_block(parser, node) != SUCCESS)
        return NULL;
    if (extract_if_expression(parser, node) != SUCCESS) {
        node_destroy(node);
        return NULL;
    }
    if (extract_if_body(parser, node) != SUCCESS) {
        node_destroy(node);
        return NULL;
    }
    return node;
}
