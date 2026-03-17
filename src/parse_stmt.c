/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** parse_stmt.c - Statement parsing for the MNC compiler
*/

#include "mncc.h"

node_t *parse_block(parser_t *p)
{
    node_t *block = new_node(NODE_BLOCK);
    int cap = 32;
    int idx = 0;

    block->children = xmalloc(sizeof(node_t *) * cap);
    expect(p, TOK_LBRACE);
    while (peek(p)->type != TOK_RBRACE && peek(p)->type != TOK_EOF) {
        block->children[idx++] = parse_stmt(p);
    }
    expect(p, TOK_RBRACE);
    block->child_count = idx;
    return block;
}

node_t *parse_decl(parser_t *p)
{
    node_t *node = new_node(NODE_DECL);

    expect(p, TOK_INT);
    node->name = strdup(peek(p)->text);
    expect(p, TOK_IDENT);
    expect(p, TOK_SEMI);
    return node;
}

node_t *parse_return_stmt(parser_t *p)
{
    node_t *node = new_node(NODE_RETURN);

    expect(p, TOK_RETURN);
    if (peek(p)->type != TOK_SEMI)
        node->left = parse_expr(p);
    expect(p, TOK_SEMI);
    return node;
}

node_t *parse_if_stmt(parser_t *p)
{
    node_t *node = new_node(NODE_IF);

    expect(p, TOK_IF);
    expect(p, TOK_LPAREN);
    node->left = parse_expr(p);
    expect(p, TOK_RPAREN);
    node->right = parse_block(p);
    if (peek(p)->type == TOK_ELSE) {
        advance(p);
        node->else_body = parse_block(p);
    }
    return node;
}

node_t *parse_while_stmt(parser_t *p)
{
    node_t *node = new_node(NODE_WHILE);

    expect(p, TOK_WHILE);
    expect(p, TOK_LPAREN);
    node->left = parse_expr(p);
    expect(p, TOK_RPAREN);
    node->right = parse_block(p);
    return node;
}

node_t *parse_assign_or_call(parser_t *p)
{
    char *name = strdup(peek(p)->text);
    node_t *node = NULL;

    advance(p);
    if (peek(p)->type == TOK_EQ) {
        advance(p);
        node = new_node(NODE_ASSIGN);
        node->left = new_node(NODE_VAR);
        node->left->name = name;
        node->right = parse_expr(p);
        expect(p, TOK_SEMI);
    } else if (peek(p)->type == TOK_LPAREN) {
        node = parse_call_args(p, name);
        free(name);
        expect(p, TOK_SEMI);
    } else {
        fprintf(stderr, "Error: unexpected token '%s' at line %d\n",
            peek(p)->text, peek(p)->line);
        free(name);
        node = new_node(NODE_VAR);
    }
    return node;
}

node_t *parse_stmt(parser_t *p)
{
    token_type_t type = peek(p)->type;

    if (type == TOK_INT)
        return parse_decl(p);
    if (type == TOK_RETURN)
        return parse_return_stmt(p);
    if (type == TOK_IF)
        return parse_if_stmt(p);
    if (type == TOK_WHILE)
        return parse_while_stmt(p);
    if (type == TOK_SEMI) {
        advance(p);
        return new_node(NODE_BLOCK);
    }
    if (type == TOK_IDENT)
        return parse_assign_or_call(p);
    fprintf(stderr, "Error: unexpected token '%s' at line %d\n",
        peek(p)->text, peek(p)->line);
    advance(p);
    return new_node(NODE_BLOCK);
}
