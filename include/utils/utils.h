/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** utils
*/

#ifndef UTILS_H_
    #define UTILS_H_
    #include "main.h"

status_t get_error(status_t code, const char *message, ...);
void *print_error(status_t code, const char *message, ...);
status_t nasm_assemble(char const *path);

#endif /* !UTILS_H_ */
