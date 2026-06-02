/*
** EPITECH PROJECT, 2026
** gen_get_registers.c
** File description:
** Generation of the get_registers function to assembly code
*/
#include "gen/gen.h"

const char *gen_get_register(int i)
{
    const char *registers[12] = {"rax",
        "rbx",
        "rcx",
        "rdx",
        "rsi",
        "rdi",
        "r8",
        "r9",
        "r10",
        "r11",
        "r12",
        "r13"};

    return registers[i];
}
