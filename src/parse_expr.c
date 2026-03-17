/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** parse_expr.c - Expression parsing for the MNC compiler
*/

#include "mncc.h"

node_t *parse_call_args(parser_t *p, char *name)
{
    node_t *node = new_node(NODE_FUNC_CALL);
    int cap = 8;
    int idx = 0;

    node->name = strdup(name);
    node->children = xmalloc(sizeof(node_t *) * cap);
    advance(p);
    while (peek(p)->type != TOK_RPAREN && peek(p)->type != TOK_EOF) {
        node->children[idx++] = parse_expr(p);
        if (peek(p)->type == TOK_COMMA)
            advance(p);
    }
    expect(p, TOK_RPAREN);
    node->child_count = idx;
    return node;
}

node_t *parse_primary_expr(parser_t *p)
{
    node_t *node = NULL;
    token_t *t = peek(p);

    if (t->type == TOK_NUMBER) {
        node = new_node(NODE_NUMBER);
        node->value = t->value;
        advance(p);
        return node;
    }
    if (t->type == TOK_IDENT) {
        char *name = strdup(t->text);
        advance(p);
        if (peek(p)->type == TOK_LPAREN)
            return parse_call_args(p, name);
        node = new_node(NODE_VAR);
        node->name = name;
        return node;
    }
    if (t->type == TOK_LPAREN) {
        advance(p);
        node = parse_expr(p);
        expect(p, TOK_RPAREN);
        return node;
    }
    fprintf(stderr, "Error: unexpected token '%s' at line %d\n",
        t->text, t->line);
    advance(p);
    return new_node(NODE_NUMBER);
}

node_t *parse_unary_expr(parser_t *p)
{
    node_t *node = NULL;

    if (peek(p)->type == TOK_MINUS) {
        advance(p);
        node = new_node(NODE_OP_NEG);
        node->left = parse_unary_expr(p);
        return node;
    }
    if (peek(p)->type == TOK_NOT) {
        advance(p);
        node = new_node(NODE_OP_NOT);
        node->left = parse_unary_expr(p);
        return node;
    }
    return parse_primary_expr(p);
}

node_t *parse_mul_expr(parser_t *p)
{
    node_t *left = parse_unary_expr(p);
    node_t *node = NULL;
    token_type_t op;

    while (peek(p)->type == TOK_MUL || peek(p)->type == TOK_DIV ||
        peek(p)->type == TOK_MOD) {
        op = peek(p)->type;
        advance(p);
        node = new_node(op == TOK_MUL ? NODE_OP_MUL :
            (op == TOK_DIV ? NODE_OP_DIV : NODE_OP_MOD));
        node->left = left;
        node->right = parse_unary_expr(p);
        left = node;
    }
    return left;
}

node_t *parse_add_expr(parser_t *p)
{
    node_t *left = parse_mul_expr(p);
    node_t *node = NULL;
    token_type_t op;

    while (peek(p)->type == TOK_PLUS || peek(p)->type == TOK_MINUS) {
        op = peek(p)->type;
        advance(p);
        node = new_node(op == TOK_PLUS ? NODE_OP_ADD : NODE_OP_SUB);
        node->left = left;
        node->right = parse_mul_expr(p);
        left = node;
    }
    return left;
}

node_t *parse_rel_expr(parser_t *p)
{
    node_t *left = parse_add_expr(p);
    node_t *node = NULL;
    token_type_t op;

    while (peek(p)->type == TOK_LT || peek(p)->type == TOK_GT ||
        peek(p)->type == TOK_LE || peek(p)->type == TOK_GE) {
        op = peek(p)->type;
        advance(p);
        node = new_node(NODE_OP_CMP);
        node->cmp_op = op;
        node->left = left;
        node->right = parse_add_expr(p);
        left = node;
    }
    return left;
}

node_t *parse_eq_expr(parser_t *p)
{
    node_t *left = parse_rel_expr(p);
    node_t *node = NULL;
    token_type_t op;

    while (peek(p)->type == TOK_EQEQ || peek(p)->type == TOK_NE) {
        op = peek(p)->type;
        advance(p);
        node = new_node(NODE_OP_CMP);
        node->cmp_op = op;
        node->left = left;
        node->right = parse_rel_expr(p);
        left = node;
    }
    return left;
}

node_t *parse_and_expr(parser_t *p)
{
    node_t *left = parse_eq_expr(p);
    node_t *node = NULL;

    while (peek(p)->type == TOK_AND) {
        advance(p);
        node = new_node(NODE_OP_AND);
        node->left = left;
        node->right = parse_eq_expr(p);
        left = node;
    }
    return left;
}

node_t *parse_or_expr(parser_t *p)
{
    node_t *left = parse_and_expr(p);
    node_t *node = NULL;

    while (peek(p)->type == TOK_OR) {
        advance(p);
        node = new_node(NODE_OP_OR);
        node->left = left;
        node->right = parse_and_expr(p);
        left = node;
    }
    return left;
}

node_t *parse_expr(parser_t *p)
{
    return parse_or_expr(p);
}
