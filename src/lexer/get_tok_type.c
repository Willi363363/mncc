/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** get_tok_type
*/

#include "lexer/lexer.h"
#include "main.h"
#include "lexer/token.h"
#include <string.h>

token_type_t get_keyword_type(const char *keyword)
{
    if (strcmp(keyword, "if") == 0)
        return TOK_IF;
    if (strcmp(keyword, "else") == 0)
        return TOK_ELSE;
    if (strcmp(keyword, "while") == 0)
        return TOK_WHILE;
    if (strcmp(keyword, "for") == 0)
        return TOK_FOR;
    if (strcmp(keyword, "return") == 0)
        return TOK_RETURN;
    if (strcmp(keyword, "int") == 0)
        return TOK_INT;
    if (strcmp(keyword, "void") == 0)
        return TOK_VOID;
    return TOK_IDENT;
}

token_type_t get_operator_type(char c)
{
    if (c == '=')
        return TOK_EQ;
    if (c == '+')
        return TOK_PLUS;
    if (c == '-')
        return TOK_MINUS;
    if (c == '*')
        return TOK_MUL;
    if (c == '/')
        return TOK_DIV;
    return TOK_EOF;
}

token_type_t get_punctuation_type(char c)
{
    if (c == ';')
        return TOK_SEMI;
    if (c == '(')
        return TOK_LPAREN;
    if (c == ')')
        return TOK_RPAREN;
    if (c == '{')
        return TOK_LBRACE;
    if (c == '}')
        return TOK_RBRACE;
    if (c == ',')
        return TOK_COMMA;
    return TOK_EOF;
}
