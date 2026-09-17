/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** binary_creation
*/

#include "asm/asm.h"
#include <stdio.h>
#include <sys/stat.h>

status_t write_elf_file(const char *path, Elf64_Ehdr *ehdr,
    Elf64_Phdr *phdr, code_buffer_t *cb)
{
    size_t written = 0;
    FILE *f = NULL;

    if (!path || !ehdr || !phdr || !cb)
        return EELF;
    f = fopen(path, "wb");
    if (!f)
        return EELF;
    written += fwrite(ehdr, 1, sizeof(Elf64_Ehdr), f);
    written += fwrite(phdr, 1, sizeof(Elf64_Phdr), f);
    written += fwrite(cb->ptr, 1, cb->len, f);
    fclose(f);
    if (written != sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + cb->len)
        return EELF;
    return (chmod(path, 0755) ? EELF : SUCCESS);
}
