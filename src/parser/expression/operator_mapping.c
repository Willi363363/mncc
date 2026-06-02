/*
** EPITECH PROJECT, 2026
** operator_mapping.c
** File description:
** Operator expression parsing function with static helpers
*/
#include "lexer/token.h"
#include "parser/node.h"
#include "parser/parser.h"

static const operator_mapping_t operator_mappings[OP_COUNT] = {{OP_EQ, TOK_EQ},
    {OP_ADD, TOK_PLUS},
    {OP_SUB, TOK_MINUS},
    {OP_MUL, TOK_MUL},
    {OP_DIV, TOK_DIV}};

static const operator_mapping_t *get_operator_mapping(operator_type_t op)
{
    for (int i = 0; i < OP_COUNT; i++) {
        if (operator_mappings[i].op == op)
            return &operator_mappings[i];
    }
    return NULL;
}

bool is_operator_token(token_t *token)
{
    for (int i = 0; i < OP_COUNT; i++) {
        if (operator_mappings[i].token == token->type)
            return true;
    }
    return false;
}

token_type_t operator_to_token(operator_type_t op)
{
    const operator_mapping_t *mapping = get_operator_mapping(op);

    if (!mapping)
        return NOIDX;
    return mapping->token;
}

operator_type_t token_to_operator(token_t *token)
{
    for (int i = 0; i < OP_COUNT; i++) {
        if (operator_mappings[i].token == token->type)
            return operator_mappings[i].op;
    }
    return OP_NONE;
}
