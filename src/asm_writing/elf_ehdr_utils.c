/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** elf_header_utils
*/

#include "asm/asm.h"
#include <string.h>

status_t init_elf_header(Elf64_Ehdr **h)
{
    if (!h)
        return EELF;
    *h = calloc(1, sizeof(Elf64_Ehdr));
    return (*h ? SUCCESS : EELF);
}

status_t destroy_elf_header(Elf64_Ehdr **h)
{
    if (!h)
        return EELF;
    free(*h);
    *h = NULL;
    return SUCCESS;
}

static status_t set_elf_identity(Elf64_Ehdr *h)
{
    if (!h)
        return EELF;
    memcpy(&(h->e_ident[EI_MAG0]), ELFMAG, SELFMAG);
    h->e_ident[EI_CLASS] = ELFCLASS64;
    h->e_ident[EI_DATA] = ELFDATA2LSB;
    h->e_ident[EI_VERSION] = EV_CURRENT;
    h->e_ident[EI_OSABI] = ELFOSABI_SYSV;
    h->e_type = ET_EXEC;
    h->e_machine = EM_X86_64;
    h->e_version = EV_CURRENT;
    return SUCCESS;
}

static status_t set_elf_section_headers(Elf64_Ehdr *h)
{
    if (!h)
        return EELF;
    h->e_shoff = 0;
    h->e_shnum = 0;
    h->e_shstrndx = 0;
    h->e_shentsize = 0;
    h->e_flags = 0;
    return SUCCESS;
}

status_t build_elf_header(Elf64_Ehdr *h, size_t entry_offset, size_t phnum)
{
    if (!h || set_elf_identity(h) == EELF || set_elf_section_headers(h) == EELF)
        return EELF;
    h->e_phoff = sizeof(Elf64_Ehdr);
    h->e_entry = ELFW_VADDR_BASE + sizeof(Elf64_Ehdr) +
        (sizeof(Elf64_Phdr) * (Elf64_Half)phnum) + entry_offset;
    h->e_ehsize = sizeof(Elf64_Ehdr);
    h->e_phentsize = sizeof(Elf64_Phdr);
    h->e_phnum = (Elf64_Half)phnum;
    return SUCCESS;
}
