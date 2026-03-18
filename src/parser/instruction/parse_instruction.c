/*
** EPITECH PROJECT, 2026
** parse_instruction.c
** File description:
** Instruction parsing functions
*/
#include <stdio.h>
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/utils.h"

static int is_data_type_token(token_t *token)
{
    return token->type == TOK_INT || token->type == TOK_VOID;
}

static int get_instruction_size(parser_t *parser)
{
    int size = 0;
    int cursor = parser->cursor;
    token_t *token = NULL;

    while (true) {
        token = parser_peek(parser);
        if (!token || token->type == TOK_SEMI)
            break;
        size++;
        parser_next(parser);
    }
    parser->cursor = cursor;
    return size;
}

static bool is_declaration(parser_t *parser, int size)
{
    token_t *token = parser_peek(parser);
    int cursor = parser->cursor;
    bool result = false;

    if (size < 3 || !(is_data_type_token(token))) {
        parser->cursor = cursor;
        return false;
    }
    if (parser_next(parser)->type != TOK_IDENT) {
        parser->cursor = cursor;
        return false;
    }
    if (parser_next(parser)->type == TOK_EQ)
        result = true;
    parser->cursor = cursor;
    return result;
}

static bool is_asignement(parser_t *parser, int size)
{
    token_t *token = parser_peek(parser);
    int cursor = parser->cursor;
    bool result = false;

    if (size < 3 || token->type != TOK_IDENT) {
        parser->cursor = cursor;
        return false;
    }
    if (parser_next(parser)->type == TOK_EQ)
        result = true;
    parser->cursor = cursor;
    return result;
}

static bool is_function_call(parser_t *parser)
{
    token_t *token = parser_peek(parser);
    int cursor = parser->cursor;
    bool result = false;

    if (token->type != TOK_IDENT) {
        parser->cursor = cursor;
        return false;
    }
    parser_next(parser);
    if (parser_peek(parser)->type == TOK_LPAREN)
        result = true;
    parser->cursor = cursor;
    return result;
}

static node_t *get_instruction_node(parser_t *parser)
{
    int size = get_instruction_size(parser);
    token_t *token = parser_peek(parser);

    if (token->type == TOK_RETURN)
        return parse_return(parser);
    if (is_declaration(parser, size))
        return parse_declaration(parser);
    if (is_function_call(parser))
        return parse_call(parser);
    if (is_asignement(parser, size))
        return parse_assignment(parser);
    get_error(EPAR, "expected instruction: got '%s'", token->value);
    return NULL;
}

node_t *parse_instruction(parser_t *parser)
{
    token_t *token = parser_peek(parser);
    node_t *node = NULL;

    if (!token) {
        get_error(EPAR, "could not parse instruction: unexpected end of file");
        return NULL;
    }
    node = get_instruction_node(parser);
    if (!node)
        return NULL;
    if (!parser_match(parser, TOK_SEMI)) {
        node_destroy(node);
        get_error(EPAR,
            "expected semicolon, got '%s'",
            parser_peek(parser)->value);
        return NULL;
    }
    parser->cursor++;
    return node;
}
