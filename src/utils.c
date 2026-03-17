/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** utils.c - Utility functions for the MNC compiler
*/

#include "mncc.h"

void *xmalloc(size_t size)
{
    void *ptr = malloc(size);

    if (!ptr) {
        fprintf(stderr, "Error: memory allocation failed\n");
        exit(84);
    }
    return ptr;
}

char *read_file(char *path)
{
    FILE *f = fopen(path, "r");
    long size = 0;
    char *buf = NULL;
    size_t nread = 0;

    if (!f) {
        fprintf(stderr, "Error: cannot open file '%s'\n", path);
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = xmalloc(size + 1);
    nread = fread(buf, 1, size, f);
    buf[nread] = '\0';
    fclose(f);
    return buf;
}

void free_tokens(token_t *tokens, int count)
{
    int i = 0;

    while (i < count) {
        free(tokens[i].text);
        i++;
    }
    free(tokens);
}

void free_node(node_t *node)
{
    int i = 0;

    if (!node)
        return;
    free_node(node->left);
    free_node(node->right);
    free_node(node->else_body);
    free_node(node->body);
    while (i < node->child_count) {
        free_node(node->children[i]);
        i++;
    }
    free(node->children);
    free(node->name);
    free(node);
}
