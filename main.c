/*
** EPITECH PROJECT, 2026
** main.c
** File description:
** mncc executable
*/

#include "main.h"
#include "utils/utils.h"
#include "lexer/token.h"
#include "lexer/lexer.h"
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static int print_usage(void)
{
    if (printf("USAGE\n\tmncc [path]\n\nDESCRIPTION\n\tpath\tmust "
            "have a main() function\n") < 0)
        return get_error(EINP, "usage print");
    return SUCCESS;
}

static int is_not_valid_file(char const *path)
{
    struct stat s = {0};

    if (!path || stat(path, &s) < 0)
        return get_error(EINP, "file not found\n%s",
            "file can't be read or doensn't exist");
    return SUCCESS;
}

static int read_file(const char *path, char **buffer)
{
    struct stat s = {0};
    int fd = 0;

    if (stat(path, &s) < 0)
        return get_error(EINP, "file open");
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return get_error(EINP, "file open"); 
    *buffer = calloc(s.st_size + 1, sizeof(char));
    if (read(fd, *buffer, s.st_size) < s.st_size) {
        free(*buffer);
        return get_error(EINP, "file open"); 
    }
    close(fd);
    return 0;
}

static int print_lexer(lexer_t *lexer)
{
    token_t *token = NULL;

    for (int i = 0; i < lexer->tokens->count; i++) {
        token = (token_t *)lexer->tokens->data[i];
        printf("Token %d: Type=%d, Value='%s'\n", i,
            token->type, token->value ? token->value : "NULL");
    }
    return SUCCESS;
}

static int run_lexer(char *buffer, lexer_t *lexer)
{
    if (lexer_tokenize(lexer, buffer) == ERROR) {
        free(buffer);
        return ERROR;
    }
    free(buffer);
    return print_lexer(lexer);
}

static int process_file(char *buffer)
{
    lexer_t *lexer = NULL;

    if (!buffer)
        return ERROR;
    lexer = lexer_create();
    if (!lexer) {
        free(buffer);
        return ERROR;
    }
    if (run_lexer(buffer, lexer) == ERROR) {
        lexer_destroy(lexer);
        return ERROR;
    }
    lexer_destroy(lexer);
    return SUCCESS;
}

int main(int ac, char **av)
{
    char *buffer = NULL;

    if (ac != 2 || !strcmp(av[1], "-h"))
        return print_usage();
    if (is_not_valid_file(av[1]))
        return ERROR;
    if (read_file(av[1], &buffer))
        return ERROR;
    if (process_file(buffer) == ERROR)
        return ERROR;
    return SUCCESS;
}
