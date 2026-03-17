/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** main.c - Entry point for the MNC compiler
*/

#include "mncc.h"

int main(int ac, char **av)
{
    char *src = NULL;
    token_t *tokens = NULL;
    node_t *ast = NULL;
    FILE *out = NULL;
    int count = 0;
    char *outpath = "output.asm";

    if (ac < 2) {
        fprintf(stderr, "Usage: %s <source.c> [output.asm]\n", av[0]);
        return 84;
    }
    if (ac >= 3)
        outpath = av[2];
    src = read_file(av[1]);
    if (!src)
        return 84;
    tokens = tokenize(src, &count);
    ast = parse(tokens, count);
    out = fopen(outpath, "w");
    if (!out) {
        fprintf(stderr, "Error: cannot open output '%s'\n", outpath);
        free_tokens(tokens, count);
        free_node(ast);
        free(src);
        return 84;
    }
    codegen(ast, out);
    fclose(out);
    free_tokens(tokens, count);
    free_node(ast);
    free(src);
    return 0;
}

