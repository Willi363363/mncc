/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** rex_modrm
*/

#include "asm/asm.h"

unsigned char make_rex(bool w, bool r, bool x, bool b)
{
    return REX_BASE | (w ? REX_W : 0) | (r ? REX_R : 0) |
        (x ? REX_X : 0) | (b ? REX_B : 0);
}

uint8_t make_modrm(mod_type_t mod, registers_t reg, registers_t rm)
{
    return (unsigned char)((mod << 6) |
        (REG_VALUE(reg) << 3) | REG_VALUE(rm));
}
