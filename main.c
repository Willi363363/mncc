/*
** EPITECH PROJECT, 2026
** main.c
** File description:
** mncc executable
*/

#include "main.h"
#include "utils/utils.h"
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

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

int main(int ac, char **av)
{
    if (ac != 2 || !strcmp(av[1], "-h"))
        return print_usage();
    if (is_not_valid_file(av[1]))
        return ERROR;
    return SUCCESS;
}
