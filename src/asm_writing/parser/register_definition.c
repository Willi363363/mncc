/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** register_definition
*/

#include "asm/asm.h"
#include <string.h>

static const reg_name_entry_t reg_names[] = {
    { "rax", REG_RAX },
    { "rcx", REG_RCX },
    { "rdx", REG_RDX },
    { "rbx", REG_RBX },
    { "rsp", REG_RSP },
    { "rbp", REG_RBP },
    { "rsi", REG_RSI },
    { "rdi", REG_RDI },
    { "r8", REG_R8 },
    { "r9", REG_R9 },
    { "r10", REG_R10 },
    { "r11", REG_R11 },
    { "r12", REG_R12 },
    { "r13", REG_R13 },
    { "r14", REG_R14 },
    { "r15", REG_R15 },
    { "al", REG_RAX },
    { "bl", REG_RBX },
    { "cl", REG_RCX },
    { "dl", REG_RDX },
};

static const size_t reg_names_len = sizeof(reg_names) / sizeof(reg_names[0]);

bool parse_register(const char *token, registers_t *out)
{
    if (!token || !out)
        return false;
    for (size_t i = 0; i < reg_names_len; i++) {
        if (strcmp(reg_names[i].name, token) == 0) {
            *out = reg_names[i].reg;
            return true;
        }
    }
    return false;
}
