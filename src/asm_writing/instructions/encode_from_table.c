/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** encode_from_table
*/

#include "asm/asm.h"

static status_t encode_rel32_form(const encode_ctx_t *e)
{
    size_t patch_at;
    size_t target;
    int32_t rel;

    if (e->n_ops < 1 || e->ops[0].kind != OPD_LABEL)
        return EELF;
    if (e->form->opcode_prefix)
        if (cb_push_1(&e->ctx->cb, e->form->opcode_prefix) != SUCCESS)
            return EELF;
    if (cb_push_1(&e->ctx->cb, e->form->opcode) != SUCCESS)
        return EELF;
    patch_at = e->ctx->cb->len;
    if (cb_push_4(&e->ctx->cb, 0) != SUCCESS)
        return EELF;
    if (symtab_lookup(e->ctx->st, e->ops[0].label, &target)) {
        rel = (int32_t)(target - (patch_at + 4));
        return cb_patch_4(&e->ctx->cb, patch_at, (uint32_t)rel);
    }
    return fixup_list_add(&e->ctx->fl, patch_at, e->ops[0].label);
}

static int find_rm_operand_index(const operand_t *ops, size_t n_ops)
{
    for (size_t i = 0; i < n_ops; i++)
        if (ops[i].kind == OPD_REG || ops[i].kind == OPD_MEM)
            return (int)i;
    return -1;
}

static status_t resolve_reg_field(const encode_ctx_t *e,
    registers_t *reg_field, int *rm_idx)
{
    int reg_idx;

    if (e->form->modrm_reg >= 0) {
        *reg_field = (registers_t)e->form->modrm_reg;
        *rm_idx = find_rm_operand_index(e->ops, e->n_ops);
        return SUCCESS;
    }
    reg_idx = e->form->reg_is_op1 ? 0 : 1;
    *rm_idx = e->form->reg_is_op1 ? 1 : 0;
    if ((size_t)reg_idx >= e->n_ops || e->ops[reg_idx].kind != OPD_REG)
        return EELF;
    *reg_field = e->ops[reg_idx].reg;
    return SUCCESS;
}

static status_t resolve_rm_operand(const encode_ctx_t *e, int rm_idx,
    modrm_info_t *info)
{
    if (rm_idx < 0 || (size_t)rm_idx >= e->n_ops)
        return EELF;
    if (e->ops[rm_idx].kind == OPD_REG) {
        info->rm_reg = e->ops[rm_idx].reg;
        return SUCCESS;
    }
    if (e->ops[rm_idx].kind == OPD_MEM) {
        info->rm_reg = e->ops[rm_idx].reg;
        info->rm_is_mem = true;
        info->mem_disp = e->ops[rm_idx].disp;
        return SUCCESS;
    }
    return EELF;
}

static status_t resolve_modrm_fields(const encode_ctx_t *e,
    modrm_info_t *info)
{
    int rm_idx = -1;

    if (resolve_reg_field(e, &info->reg_field, &rm_idx) != SUCCESS)
        return EELF;
    return resolve_rm_operand(e, rm_idx, info);
}

static status_t encode_rex(const encode_ctx_t *e, const modrm_info_t *info)
{
    bool r_bit = (e->form->has_modrm && e->form->modrm_reg < 0) ?
        REG_REX_VALUE(info->reg_field) : false;
    bool b_bit = false;

    if (e->form->has_modrm)
        b_bit = REG_REX_VALUE(info->rm_reg);
    if (!e->form->has_modrm && e->form->plus_reg && e->n_ops >= 1 &&
        e->ops[0].kind == OPD_REG)
        b_bit = REG_REX_VALUE(e->ops[0].reg);
    if (!e->form->needs_rex_w && !r_bit && !b_bit)
        return SUCCESS;
    return cb_push_1(&e->ctx->cb,
        make_rex(e->form->needs_rex_w, r_bit, false, b_bit));
}

static status_t encode_opcode(const encode_ctx_t *e)
{
    uint8_t opcode_byte = e->form->opcode;

    if (e->form->opcode_prefix)
        if (cb_push_1(&e->ctx->cb, e->form->opcode_prefix) != SUCCESS)
            return EELF;
    if (e->form->plus_reg && e->n_ops >= 1 && e->ops[0].kind == OPD_REG)
        opcode_byte = (uint8_t)(e->form->opcode + REG_VALUE(e->ops[0].reg));
    return cb_push_1(&e->ctx->cb, opcode_byte);
}

static status_t encode_modrm_bytes(const encode_ctx_t *e,
    const modrm_info_t *info)
{
    mod_type_t mod = info->rm_is_mem ? MOD_DISP8 : MOD_DIRECT;
    unsigned char modrm = make_modrm(mod, info->reg_field, info->rm_reg);

    if (cb_push_1(&e->ctx->cb, modrm) != SUCCESS)
        return EELF;
    if (!info->rm_is_mem)
        return SUCCESS;
    return cb_push_1(&e->ctx->cb, (uint8_t)info->mem_disp);
}

static status_t encode_immediate(const encode_ctx_t *e)
{
    int64_t imm = 0;

    if (e->n_ops >= 2 && e->ops[1].kind == OPD_IMM)
        imm = e->ops[1].imm;
    if (e->form->imm_size == 8)
        return cb_push_8(&e->ctx->cb, (uint64_t)imm);
    if (e->form->imm_size == 4)
        return cb_push_4(&e->ctx->cb, (uint32_t)imm);
    if (e->form->imm_size == 1)
        return cb_push_1(&e->ctx->cb, (uint8_t)imm);
    return SUCCESS;
}

status_t encode_from_table(asm_ctx_t *ctx, const instr_form_t *form,
    const operand_t *ops, size_t n_ops)
{
    encode_ctx_t e = {ctx, form, ops, n_ops};
    modrm_info_t info = {REG_RAX, REG_RAX, false, 0};

    if (!ctx || !ctx->cb || !form)
        return EELF;
    if (form->is_rel32)
        return encode_rel32_form(&e);
    if (form->has_modrm && resolve_modrm_fields(&e, &info) != SUCCESS)
        return EELF;
    if (encode_rex(&e, &info) != SUCCESS)
        return EELF;
    if (encode_opcode(&e) != SUCCESS)
        return EELF;
    if (form->has_modrm && encode_modrm_bytes(&e, &info) != SUCCESS)
        return EELF;
    return encode_immediate(&e);
}
