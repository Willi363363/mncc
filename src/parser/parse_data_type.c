/*
** EPITECH PROJECT, 2026
** parse_data_type.c
** File description:
** Data type parsing function
*/
#include <errno.h>
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/array.h"
#include "utils/utils.h"

static data_type_t handle_pointer(parser_t *parser, data_type_t base_type)
{
    bool is_pointer = false;

    while (parser_peek(parser)->type == TOK_MUL) {
        parser_next(parser);
        is_pointer = true;
    }
    return is_pointer ? DATA_POINTER : base_type;
}

data_type_t parse_data_type(parser_t *parser)
{
    token_t *token = parser_peek(parser);

    if (token->type == TOK_INT) {
        parser_next(parser);
        return handle_pointer(parser, DATA_INT);
    }
    get_error(EPAR, "expected a data type, got '%s'", token->value);
    return DATA_INVALID;
}
