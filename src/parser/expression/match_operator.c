/*
** EPITECH PROJECT, 2026
** match_operator.c
** File description:
** Operator expression parsing function with static helpers
*/
#include "lexer/token.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/array.h"

static const operator_mapping_t operator_mappings[OPERATOR_COUNT] = {
    {OP_EQUAL, {TOK_EQ, TOK_EQ, TOK_EOF}},
    {OP_ADD, {TOK_PLUS, TOK_EOF, TOK_EOF}},
    {OP_SUB, {TOK_MINUS, TOK_EOF, TOK_EOF}},
    {OP_MUL, {TOK_MUL, TOK_EOF, TOK_EOF}},
    {OP_DIV, {TOK_DIV, TOK_EOF, TOK_EOF}}};

static const operator_mapping_t *get_operator_mapping(operator_type_t op)
{
    for (int i = 0; i < OPERATOR_COUNT; i++) {
        if (operator_mappings[i].op == op)
            return &operator_mappings[i];
    }
    return NULL;
}

int get_operator_size(operator_type_t op)
{
    const operator_mapping_t *operator = get_operator_mapping(op);
    int i = 0;

    while (operator->tokens[i] != TOK_EOF)
        i++;
    return i;
}

bool tokens_match_operator(token_t **tokens, operator_type_t op)
{
    bool match = true;
    const operator_mapping_t *operator = get_operator_mapping(op);

    for (int i = 0; operator->tokens[i] != TOK_EOF; i++) {
        if (tokens[i]->type != operator->tokens[i]) {
            match = false;
            break;
        }
    }
    return match;
}

operator_type_t tokens_to_operator(token_t **tokens)
{
    for (int i = 0; i < OPERATOR_COUNT; i++) {
        if (tokens_match_operator(tokens, i))
            return operator_mappings[i].op;
    }
    return OP_INVALID;
}

int get_operator_offset(parser_t *parser, int size, operator_type_t op)
{
    token_t **all_tokens = (token_t **)parser->lexer->tokens->data;
    token_t **tokens = all_tokens + parser->cursor;
    int depth = 0;

    for (int i = 0; i < size; i++) {
        if (tokens[0]->type == TOK_LPAREN)
            depth++;
        if (tokens[0]->type == TOK_RPAREN)
            depth--;
        if (tokens_match_operator(tokens, op) && depth == 0) {
            return i;
        }
        tokens++;
    }
    return -1;
}
