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
    #include <stdbool.h>
    #include "main.h"
    #include "asm/asm_types.h"

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
status_t cb_patch_4(code_buffer_t **cb, size_t offset, uint32_t v);
status_t cb_pos(code_buffer_t *cb, size_t *len);

// Section Header Writing
status_t build_elf_header(Elf64_Ehdr *h, size_t entry_offset, size_t phnum);
status_t destroy_elf_header(Elf64_Ehdr **h);
status_t init_elf_header(Elf64_Ehdr **h);

// Program Header Writing
status_t build_phdr(Elf64_Phdr *h, size_t p_len);
status_t destroy_phdr(Elf64_Phdr **h);
status_t init_phdr(Elf64_Phdr **h);

// Binary Writing
status_t write_elf_file(const char *path, Elf64_Ehdr *ehdr,
    Elf64_Phdr *phdr, code_buffer_t *cb);

// Symtabs management
status_t symtab_init(symtab_t **st);
status_t symtab_free(symtab_t **st);
status_t symtab_define(symtab_t **st, const char *name, size_t offset);
bool symtab_lookup(symtab_t *st, const char *name, size_t *out_offset);

// Fixups

status_t fixup_list_init(fixup_list_t **fl);
status_t fixup_list_add(fixup_list_t **fl,
    size_t patch_offset, const char *symbol);
status_t fixup_list_free(fixup_list_t **fl);

#endif /* !ASM_H_ */
