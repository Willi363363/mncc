/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** parser.c - Top-level parser for the MNC compiler
*/

#include "mncc.h"

node_t *new_node(node_type_t type)
{
    node_t *node = xmalloc(sizeof(node_t));

    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->else_body = NULL;
    node->body = NULL;
    node->value = 0;
    node->name = NULL;
    node->children = NULL;
    node->child_count = 0;
    node->cmp_op = 0;
    return node;
}

token_t *peek(parser_t *p)
{
    return &p->tokens[p->pos];
}

token_t *advance(parser_t *p)
{
    token_t *t = &p->tokens[p->pos];

    if (p->pos < p->count - 1)
        p->pos++;
    return t;
}

int expect(parser_t *p, token_type_t type)
{
    if (peek(p)->type != type) {
        fprintf(stderr, "Error: expected token %d, got %d ('%s') at line %d\n",
            type, peek(p)->type, peek(p)->text, peek(p)->line);
        return 0;
    }
    advance(p);
    return 1;
}

node_t *parse_func_def(parser_t *p)
{
    node_t *node = new_node(NODE_FUNC_DEF);
    int cap = 8;
    int idx = 0;

    expect(p, TOK_INT);
    node->name = strdup(peek(p)->text);
    expect(p, TOK_IDENT);
    expect(p, TOK_LPAREN);
    node->children = xmalloc(sizeof(node_t *) * cap);
    while (peek(p)->type != TOK_RPAREN && peek(p)->type != TOK_EOF) {
        expect(p, TOK_INT);
        node->children[idx] = new_node(NODE_VAR);
        node->children[idx]->name = strdup(peek(p)->text);
        expect(p, TOK_IDENT);
        idx++;
        if (peek(p)->type == TOK_COMMA)
            advance(p);
    }
    expect(p, TOK_RPAREN);
    node->child_count = idx;
    node->body = parse_block(p);
    return node;
}

node_t *parse(token_t *tokens, int count)
{
    parser_t p;
    node_t *program = new_node(NODE_BLOCK);
    int cap = 16;
    int idx = 0;

    p.tokens = tokens;
    p.pos = 0;
    p.count = count;
    program->children = xmalloc(sizeof(node_t *) * cap);
    while (peek(&p)->type != TOK_EOF) {
        if (peek(&p)->type == TOK_INT) {
            program->children[idx++] = parse_func_def(&p);
        } else {
            fprintf(stderr, "Error: expected function at line %d\n",
                peek(&p)->line);
            break;
        }
    }
    program->child_count = idx;
    return program;
}
