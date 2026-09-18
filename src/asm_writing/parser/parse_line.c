/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** parse_line
*/

#include <string.h>
#include "asm/asm.h"

static bool is_directive(const token_list_t *tl)
{
    return tl->count >= 1 &&
        (!strcmp(tl->items[0], "section") ||
        !strcmp(tl->items[0], "global"));
}

static status_t parse_operands(const token_list_t *tl, operand_t *ops,
    size_t n_ops)
{
    for (size_t i = 0; i < n_ops; i++)
        if (parse_operand(tl->items[i + 1], &ops[i]) != SUCCESS)
            return EELF;
    return SUCCESS;
}

static status_t encode_instruction(asm_ctx_t *ctx, const token_list_t *tl)
{
    const char *mnemonic = tl->items[0];
    operand_t ops[2];
    size_t n_ops = tl->count - 1;
    const instr_form_t *form = NULL;

    if (n_ops > 2)
        return EELF;
    if (parse_operands(tl, ops, n_ops) != SUCCESS)
        return EELF;
    if (find_instr_form(mnemonic, ops, n_ops, &form) != SUCCESS)
        return EELF;
    return encode_from_table(ctx, form, ops, n_ops);
}

status_t parse_line(asm_ctx_t *ctx, const char *line)
{
    token_list_t tl;
    char label_name[256];

    if (tokenize_line(line, &tl) != SUCCESS)
        return EELF;
    if (tl.count == 0 || is_directive(&tl))
        return SUCCESS;
    if (is_label_definition(&tl, label_name, sizeof(label_name)))
        return symtab_define(&ctx->st, label_name, ctx->cb->len);
    return encode_instruction(ctx, &tl);
}
