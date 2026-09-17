/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** find_instruction_form
*/

#include <string.h>
#include "asm/asm.h"

static operand_kind_t kind_at(const operand_t *ops,
    size_t n_ops, size_t idx)
{
    if (!ops)
        return OPD_NONE;
    return (idx < n_ops) ? ops[idx].kind : OPD_NONE;
}

status_t find_instr_form(const char *mnemonic, const operand_t *ops,
    size_t n_ops, const instr_form_t **f)
{
    operand_kind_t k[2] = {OPD_NONE, OPD_NONE};

    if (!mnemonic || !f)
        return EELF;
    k[0] = kind_at(ops, n_ops, 0);
    k[1] = kind_at(ops, n_ops, 1);
    for (size_t i = 0; i < instr_table_len; i++) {
        if (strcmp(instr_table[i].mnemonic, mnemonic))
            continue;
        if (instr_table[i].op1_kind != k[0])
            continue;
        if (instr_table[i].op2_kind != k[1])
            continue;
        *f = &instr_table[i];
        return SUCCESS;
    }
    return EELF;
}
