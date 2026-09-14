/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** elf_phdr_utils
*/

#include "asm/asm.h"
#include <string.h>

status_t init_phdr(Elf64_Phdr **h)
{
    if (!h)
        return EELF;
    *h = calloc(1, sizeof(Elf64_Phdr));
    return (*h ? SUCCESS : EELF);
}

status_t destroy_phdr(Elf64_Phdr **h)
{
    if (!h)
        return EELF;
    free(*h);
    *h = NULL;
    return SUCCESS;
}

status_t build_phdr(Elf64_Phdr *h, size_t p_len)
{
    if (!h)
        return EELF;
    h->p_type = PT_LOAD;
    h->p_flags = PF_R | PF_X;
    h->p_offset = 0;
    h->p_vaddr = ELFW_VADDR_BASE;
    h->p_paddr = ELFW_VADDR_BASE;
    h->p_filesz = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + p_len;
    h->p_memsz = sizeof(Elf64_Ehdr) + sizeof(Elf64_Phdr) + p_len;
    h->p_align = ELFW_PHDR_ALIGN;
    return SUCCESS;
}
