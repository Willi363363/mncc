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

//Helper functions
status_t cb_init(code_buffer_t **cb);
status_t cb_clear(code_buffer_t **cb);
status_t cb_destroy(code_buffer_t **cb);
status_t cb_adjust(code_buffer_t **cb, size_t add_size);
status_t cb_pos(code_buffer_t *cb, size_t *len);

// Data push functions
status_t cb_push_1(code_buffer_t **cb, unsigned char v);
status_t cb_push_2(code_buffer_t **cb, u_int16_t v);
status_t cb_push_4(code_buffer_t **cb, u_int32_t v);
status_t cb_push_8(code_buffer_t **cb, uint64_t v);

// Data patch functions
status_t cb_patch_8(code_buffer_t **cb, size_t offset, uint64_t v);

#endif /* !ASM_H_ */
