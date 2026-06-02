/*
** EPITECH PROJECT, 2026
** main.h
** File description:
** Main header file, containing common definitions
*/

#ifndef MAIN_H_
    #define MAIN_H_
    #define STDERR (int)(2)
    #define STDOUT (int)(1)
    #define NOIDX (ssize_t)(-1)
    #include <asm-generic/errno-base.h>

typedef enum status_e {
    SUCCESS,
    ELEX,
    EPARSE,
    EGEN,
    EMEM,
    EIMP
} status_t;

#endif /* !MAIN_H_ */
