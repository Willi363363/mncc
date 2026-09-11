/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** asm
*/

#ifndef ASM_H_
    #define ASM_H_

    #include <elf.h>
    #include <sys/types.h>
    #include <stdlib.h>
    #include "main.h"

    #define CB_BUFFER_CAPACITY (size_t)(2048)

typedef struct code_buffer_s {
    unsigned char *ptr;
    size_t len;
    size_t tot;
} code_buffer_t;

#endif /* !ASM_H_ */
