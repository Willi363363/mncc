/*
** EPITECH PROJECT, 2026
** main.c
** File description:
** mncc executable
*/
#include "main.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "gen/gen.h"
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "utils/utils.h"

static int print_usage(void)
{
    if (printf("USAGE\n\tmncc [path]\n\nDESCRIPTION"
            "\n\tpath\tmust have a main() function\n") <= 0)
        return get_error(EIMP, "usage print");
    return SUCCESS;
}

static int is_not_valid_file(char const *path)
{
    struct stat s = {0};

    if (!path || stat(path, &s) < 0)
        return get_error(
            EIMP, "file not found\n%s", "file can't be read or doensn't exist");
    return SUCCESS;
}

static int read_file(const char *path, char **buffer)
{
    struct stat s = {0};
    int fd = 0;

    if (stat(path, &s) < 0)
        return get_error(EIMP, "file open");
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return get_error(EIMP, "file open");
    *buffer = calloc(s.st_size + 1, sizeof(char));
    if (read(fd, *buffer, s.st_size) < s.st_size) {
        free(*buffer);
        *buffer = NULL;
        close(fd);
        return get_error(EIMP, "file open");
    }
    close(fd);
    return 0;
}

static int process_generation(parser_t *parser)
{
    gen_t *gen = gen_create(".github/a.asm", parser);
    int result = SUCCESS;

    if (!gen)
        return EGEN;
    result = gen_run(gen);
    gen_destroy(gen);
    nasm_assemble(".github/a.asm");
    return result;
}

static int process_parsing(lexer_t *lexer)
{
    parser_t *parser = parser_create(lexer);
    int result = SUCCESS;

    if (!parser)
        return EPARSE;
    result = parser_run(parser);
    if (result == SUCCESS)
        result = process_generation(parser);
    parser_destroy(parser);
    return result;
}

static status_t process_file(char *path)
{
    char *buffer = NULL;
    lexer_t *lexer = NULL;

    if (read_file(path, &buffer) || !buffer)
        return EIMP;
    lexer = lexer_create(buffer);
    if (!lexer) {
        free(buffer);
        return EMEM;
    }
    if (lexer_run(lexer) != SUCCESS) {
        lexer_destroy(lexer);
        return ELEX;
    }
    process_parsing(lexer);
    lexer_destroy(lexer);
    return SUCCESS;
}

int main(int ac, char **av)
{
    if (ac != 2 || !strcmp(av[1], "-h"))
        return print_usage();
    if (is_not_valid_file(av[1]))
        return EIMP;
    return process_file(av[1]);
}
