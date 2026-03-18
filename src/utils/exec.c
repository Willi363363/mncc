/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** exec
*/

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "main.h"
#include "utils.h"

int nasm_assemble(char const *path)
{
    pid_t pid = 0;
    int status = 0;
    char *argv[] = {"sh", "./assemble.sh", (char *)path, NULL};

    if (!path)
        return get_error(EGEN, "Null path sent for execution%s",
            "\nAt: nasm_assemble");
    pid = fork();
    if (pid == -1)
        return get_error(EGEN, "fork failed");
    if (pid == 0) {
        execvp("sh", argv);
        exit(EGEN);
    }
    waitpid(pid, &status, 0);
    if (!WIFEXITED(status))
        return get_error(EGEN, "assemble.sh execution failed");
    if (WEXITSTATUS(status) != 0)
        return get_error(EGEN, "assemble.sh returned error code");
    return SUCCESS;
}