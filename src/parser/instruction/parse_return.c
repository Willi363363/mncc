/*
** EPITECH PROJECT, 2026
** parse_return.c
** File description:
** Return instruction parsing function
*/
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/array.h"
#include "utils/utils.h"

static status_t add_expression_to_return_node(parser_t *parser, node_t *node)
{
    node_t *expression = parse_expression(parser);

    if (!expression)
        return get_error(EMEM, "parser 'return' node child allocation");
    if (array_push(node->childs, expression) != SUCCESS) {
        node_destroy(expression);
        return get_error(EMEM, "parser 'return' node child implementation");
    }
    return SUCCESS;
}

node_t *parse_return(parser_t *parser)
{
    node_t *node = node_create(NODE_RETURN);

    if (!node)
        return print_error(EMEM, "parser 'return' node allocation");
    if (parser_next(parser)->type == TOK_SEMI)
        return node;
    if (add_expression_to_return_node(parser, node) != SUCCESS) {
        node_destroy(node);
        return NULL;
    }
    return node;
}
