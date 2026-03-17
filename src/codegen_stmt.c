/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** codegen_stmt.c - Statement code generation for the MNC compiler
*/

#include "mncc.h"

void gen_assign(node_t *node, codegen_ctx_t *ctx)
{
    int offset = find_local(ctx, node->left->name);

    gen_expr(node->right, ctx);
    if (offset > 0)
        fprintf(ctx->out, "    mov [rbp - %d], rax\n", offset);
    else
        fprintf(stderr, "Error: undeclared variable '%s'\n",
            node->left->name);
}

void gen_return(node_t *node, codegen_ctx_t *ctx)
{
    if (node->left)
        gen_expr(node->left, ctx);
    fprintf(ctx->out, "    jmp .%s_end\n", ctx->func_name);
}

void gen_if(node_t *node, codegen_ctx_t *ctx)
{
    int lbl = ctx->label_count++;

    gen_expr(node->left, ctx);
    fprintf(ctx->out, "    cmp rax, 0\n");
    fprintf(ctx->out, "    je .else%d\n", lbl);
    gen_block(node->right, ctx);
    fprintf(ctx->out, "    jmp .end%d\n", lbl);
    fprintf(ctx->out, ".else%d:\n", lbl);
    if (node->else_body)
        gen_block(node->else_body, ctx);
    fprintf(ctx->out, ".end%d:\n", lbl);
}

void gen_while(node_t *node, codegen_ctx_t *ctx)
{
    int lbl = ctx->label_count++;

    fprintf(ctx->out, ".while%d:\n", lbl);
    gen_expr(node->left, ctx);
    fprintf(ctx->out, "    cmp rax, 0\n");
    fprintf(ctx->out, "    je .wend%d\n", lbl);
    gen_block(node->right, ctx);
    fprintf(ctx->out, "    jmp .while%d\n", lbl);
    fprintf(ctx->out, ".wend%d:\n", lbl);
}

void gen_stmt(node_t *node, codegen_ctx_t *ctx)
{
    if (!node)
        return;
    if (node->type == NODE_ASSIGN)
        gen_assign(node, ctx);
    else if (node->type == NODE_RETURN)
        gen_return(node, ctx);
    else if (node->type == NODE_IF)
        gen_if(node, ctx);
    else if (node->type == NODE_WHILE)
        gen_while(node, ctx);
    else if (node->type == NODE_FUNC_CALL) {
        gen_call(node, ctx);
    } else if (node->type == NODE_BLOCK || node->type == NODE_DECL) {
        return;
    } else {
        fprintf(stderr, "Warning: unhandled statement type %d\n",
            node->type);
    }
}

void gen_block(node_t *node, codegen_ctx_t *ctx)
{
    int i = 0;

    if (!node || node->type != NODE_BLOCK)
        return;
    while (i < node->child_count) {
        gen_stmt(node->children[i], ctx);
        i++;
    }
}
