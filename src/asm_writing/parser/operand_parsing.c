/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** operand_parsing
*/

#include <string.h>
#include "asm/asm.h"

static status_t try_parse_register(const char *token, operand_t *out)
{
    registers_t reg;

    if (!parse_register(token, &reg))
        return EELF;
    out->kind = OPD_REG;
    out->reg = reg;
    return SUCCESS;
}

static status_t try_parse_immediate(const char *token, operand_t *out)
{
    char *endptr;
    long val;

    if (token[0] != '-' && (token[0] < '0' || token[0] > '9'))
        return EELF;
    val = strtol(token, &endptr, 0);
    if (*endptr != '\0')
        return EELF;
    out->kind = OPD_IMM;
    out->imm = val;
    return SUCCESS;
}

static status_t extract_inner(const char *token, size_t len, char *inner,
    size_t inner_cap)
{
    size_t inner_len = len - 2;

    if (inner_len >= inner_cap)
        return EELF;
    strncpy(inner, &token[1], inner_len);
    inner[inner_len] = '\0';
    return SUCCESS;
}

static size_t skip_spaces(const char *s, size_t i)
{
    while (s[i] == ' ')
        i++;
    return i;
}

static void split_base_and_disp(const char *inner, char *base_name,
    int *disp)
{
    size_t i = skip_spaces(inner, 0);
    size_t j = 0;
    char sign;

    while (inner[i] && inner[i] != '+' && inner[i] != '-' &&
        inner[i] != ' ') {
        base_name[j] = inner[i];
        i++;
        j++;
    }
    base_name[j] = '\0';
    i = skip_spaces(inner, i);
    if (!inner[i])
        return;
    sign = inner[i];
    i = skip_spaces(inner, i + 1);
    *disp = (int)strtol(&inner[i], NULL, 0);
    if (sign == '-')
        *disp = -(*disp);
}

static status_t try_parse_memory(const char *token, size_t len,
    operand_t *out)
{
    char inner[MAX_TOKEN_LEN];
    char base_name[16] = {0};
    int disp = 0;
    registers_t base_reg;

    if (token[0] != '[' || token[len - 1] != ']')
        return EELF;
    if (extract_inner(token, len, inner, sizeof(inner)) != SUCCESS)
        return EELF;
    split_base_and_disp(inner, base_name, &disp);
    if (!parse_register(base_name, &base_reg))
        return EELF;
    out->kind = OPD_MEM;
    out->reg = base_reg;
    out->disp = (int8_t)disp;
    return SUCCESS;
}

static status_t parse_label(const char *token, operand_t *out)
{
    out->kind = OPD_LABEL;
    strncpy(out->label, token, sizeof(out->label) - 1);
    out->label[sizeof(out->label) - 1] = '\0';
    return SUCCESS;
}

status_t parse_operand(const char *token, operand_t *out)
{
    size_t len;

    if (!token || !out)
        return EELF;
    len = strlen(token);
    if (len == 0)
        return EELF;
    if (try_parse_register(token, out) == SUCCESS)
        return SUCCESS;
    if (try_parse_immediate(token, out) == SUCCESS)
        return SUCCESS;
    if (try_parse_memory(token, len, out) == SUCCESS)
        return SUCCESS;
    return parse_label(token, out);
}
