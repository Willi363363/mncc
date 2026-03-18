/*
** EPITECH PROJECT, 2026
** main.c
** File description:
** mncc executable
*/

#include "main.h"
#include "utils/utils.h"
#include "lexer/lexer.h"
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

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

static int read_file_content(FILE *file, char **buffer, long length)
{
    *buffer = calloc(length + 1, sizeof(char));
    if (!*buffer)
        return get_error(ENOMEM, "file buffer allocation");
    if (fread(*buffer, 1, length, file) != (size_t)length) {
        free(*buffer);
        return get_error(EINP, "file read");
    }
    (*buffer)[length] = '\0';
    return SUCCESS;
}

static int read_file(const char *path, char **buffer)
{
    FILE *file = fopen(path, "r");
    long length = 0;
    int result = 0;

    if (!file)
        return get_error(EINP, "file open");
    fseek(file, 0, SEEK_END);
    length = ftell(file);
    fseek(file, 0, SEEK_SET);
    result = read_file_content(file, buffer, length);
    fclose(file);
    return result;
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
    if (lexer_tokenize(lexer, buffer) == ERROR) {
        lexer_destroy(lexer);
        free(buffer);
        return ERROR;
    }
    free(buffer);
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
