/*
** EPITECH PROJECT, 2026
** parse_expression.c
** File description:
** Expression parsing function
*/
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/utils.h"

node_t *parse_expression_with_size(parser_t *parser, size_t size)
{
    node_t *node = NULL;

    if (expression_pre_clean(parser, &size) != SUCCESS)
        return NULL;
    if (get_operator_offset(parser, size) != NOIDX)
        node = parse_expression_with_operator(parser, size);
    else
        node = parse_value(parser);
    if (!node)
        return print_error(EPARSE,
            "invalid expression '%s'",
            parser_peek(parser) ? parser_peek(parser)->value : "end of input");
    return node;
}

node_t *parse_expression(parser_t *parser)
{
    size_t size = get_expression_size(parser);

    if (size <= 0)
        return print_error(EPARSE,
            "unexpected token '%s' while parsing expression",
            parser_peek(parser) ? parser_peek(parser)->value : "end of input");
    return parse_expression_with_size(parser, size);
}
