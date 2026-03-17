/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** codegen_expr.c - Expression code generation for the MNC compiler
*/

#include "mncc.h"

void gen_cmp(node_t *node, codegen_ctx_t *ctx)
{
    gen_expr(node->left, ctx);
    fprintf(ctx->out, "    push rax\n");
    gen_expr(node->right, ctx);
    fprintf(ctx->out, "    pop rbx\n");
    fprintf(ctx->out, "    cmp rbx, rax\n");
    fprintf(ctx->out, "    mov rax, 0\n");
    if (node->cmp_op == TOK_LT)
        fprintf(ctx->out, "    setl al\n");
    else if (node->cmp_op == TOK_GT)
        fprintf(ctx->out, "    setg al\n");
    else if (node->cmp_op == TOK_LE)
        fprintf(ctx->out, "    setle al\n");
    else if (node->cmp_op == TOK_GE)
        fprintf(ctx->out, "    setge al\n");
    else if (node->cmp_op == TOK_EQEQ)
        fprintf(ctx->out, "    sete al\n");
    else if (node->cmp_op == TOK_NE)
        fprintf(ctx->out, "    setne al\n");
    fprintf(ctx->out, "    movzx rax, al\n");
}

void gen_binop(node_t *node, codegen_ctx_t *ctx)
{
    if (node->type == NODE_OP_CMP) {
        gen_cmp(node, ctx);
        return;
    }
    gen_expr(node->left, ctx);
    fprintf(ctx->out, "    push rax\n");
    gen_expr(node->right, ctx);
    fprintf(ctx->out, "    pop rbx\n");
    if (node->type == NODE_OP_ADD)
        fprintf(ctx->out, "    add rax, rbx\n");
    else if (node->type == NODE_OP_SUB)
        fprintf(ctx->out, "    sub rbx, rax\n    mov rax, rbx\n");
    else if (node->type == NODE_OP_MUL)
        fprintf(ctx->out, "    imul rax, rbx\n");
    else if (node->type == NODE_OP_DIV) {
        fprintf(ctx->out, "    mov rcx, rax\n");
        fprintf(ctx->out, "    mov rax, rbx\n");
        fprintf(ctx->out, "    cqo\n    idiv rcx\n");
    } else if (node->type == NODE_OP_MOD) {
        fprintf(ctx->out, "    mov rcx, rax\n");
        fprintf(ctx->out, "    mov rax, rbx\n");
        fprintf(ctx->out, "    cqo\n    idiv rcx\n    mov rax, rdx\n");
    }
}

void gen_call(node_t *node, codegen_ctx_t *ctx)
{
    char *regs[] = {"rdi", "rsi", "rdx", "rcx", "r8", "r9"};
    int i = 0;

    while (i < node->child_count && i < 6) {
        gen_expr(node->children[i], ctx);
        fprintf(ctx->out, "    mov %s, rax\n", regs[i]);
        i++;
    }
    fprintf(ctx->out, "    call %s\n", node->name);
}

void gen_expr(node_t *node, codegen_ctx_t *ctx)
{
    int offset = 0;

    if (!node)
        return;
    if (node->type == NODE_NUMBER) {
        fprintf(ctx->out, "    mov rax, %d\n", node->value);
    } else if (node->type == NODE_VAR) {
        offset = find_local(ctx, node->name);
        if (offset > 0)
            fprintf(ctx->out, "    mov rax, [rbp - %d]\n", offset);
        else
            fprintf(stderr, "Error: undeclared variable '%s'\n", node->name);
    } else if (node->type == NODE_OP_NEG) {
        gen_expr(node->left, ctx);
        fprintf(ctx->out, "    neg rax\n");
    } else if (node->type == NODE_OP_NOT) {
        gen_expr(node->left, ctx);
        fprintf(ctx->out, "    cmp rax, 0\n");
        fprintf(ctx->out, "    sete al\n    movzx rax, al\n");
    } else if (node->type == NODE_OP_AND) {
        gen_expr(node->left, ctx);
        fprintf(ctx->out, "    push rax\n");
        gen_expr(node->right, ctx);
        fprintf(ctx->out, "    pop rbx\n");
        fprintf(ctx->out, "    test rax, rax\n    setne al\n");
        fprintf(ctx->out, "    test rbx, rbx\n    setne bl\n");
        fprintf(ctx->out, "    and al, bl\n    movzx rax, al\n");
    } else if (node->type == NODE_OP_OR) {
        gen_expr(node->left, ctx);
        fprintf(ctx->out, "    push rax\n");
        gen_expr(node->right, ctx);
        fprintf(ctx->out, "    pop rbx\n");
        fprintf(ctx->out, "    test rax, rax\n    setne al\n");
        fprintf(ctx->out, "    test rbx, rbx\n    setne bl\n");
        fprintf(ctx->out, "    or al, bl\n    movzx rax, al\n");
    } else if (node->type == NODE_FUNC_CALL) {
        gen_call(node, ctx);
    } else {
        gen_binop(node, ctx);
    }
}
