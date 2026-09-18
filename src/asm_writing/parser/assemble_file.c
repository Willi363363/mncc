/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** assemble_file
*/

#include "asm/asm.h"
#include <stdio.h>

static status_t init_context(asm_ctx_t *ctx)
{
    if (cb_init(&ctx->cb) != SUCCESS ||
        symtab_init(&ctx->st) != SUCCESS ||
        fixup_list_init(&ctx->fl) != SUCCESS)
        return EELF;
    return SUCCESS;
}

static status_t parse_file_lines(asm_ctx_t *ctx, FILE *f)
{
    char line[512];

    while (fgets(line, sizeof(line), f))
        if (parse_line(ctx, line) != SUCCESS)
            return EELF;
    return SUCCESS;
}

static status_t build_elf_output(const char *out_path, asm_ctx_t *ctx,
    size_t entry_offset)
{
    Elf64_Ehdr *ehdr = NULL;
    Elf64_Phdr *phdr = NULL;
    status_t result = SUCCESS;

    if (init_elf_header(&ehdr) != SUCCESS ||
        build_elf_header(ehdr, entry_offset, 1) != SUCCESS ||
        init_phdr(&phdr) != SUCCESS ||
        build_phdr(phdr, ctx->cb->len) != SUCCESS ||
        write_elf_file(out_path, ehdr, phdr, ctx->cb) != SUCCESS)
        result = EELF;
    destroy_elf_header(&ehdr);
    destroy_phdr(&phdr);
    return result;
}

static status_t write_output(const char *out_path, asm_ctx_t *ctx)
{
    size_t entry_offset;

    if (!symtab_lookup(ctx->st, "_start", &entry_offset))
        return EELF;
    return build_elf_output(out_path, ctx, entry_offset);
}

static void destroy_context(asm_ctx_t *ctx)
{
    cb_destroy(&ctx->cb);
    symtab_free(&ctx->st);
    fixup_list_free(&ctx->fl);
}

status_t assemble_file(const char *asm_path, const char *out_path)
{
    FILE *f;
    asm_ctx_t ctx = {0};
    status_t result;

    f = fopen(asm_path, "r");
    if (!f)
        return EELF;
    if (init_context(&ctx) != SUCCESS) {
        fclose(f);
        return EELF;
    }
    result = parse_file_lines(&ctx, f);
    fclose(f);
    if (result == SUCCESS)
        result = fixup_list_resolve(ctx.fl, ctx.st, &ctx.cb);
    if (result == SUCCESS)
        result = write_output(out_path, &ctx);
    destroy_context(&ctx);
    return result;
}
