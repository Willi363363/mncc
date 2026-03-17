/*
** EPITECH PROJECT, 2026
** mncc
** File description:
** lexer_op.c - Operator and whitespace lexing for MNC
*/

#include "mncc.h"

void skip_line_comment(lexer_t *lex)
{
    while (lex->src[lex->pos] && lex->src[lex->pos] != '\n')
        lex->pos++;
}

void skip_block_comment(lexer_t *lex)
{
    lex->pos += 2;
    while (lex->src[lex->pos] &&
        !(lex->src[lex->pos] == '*' && lex->src[lex->pos + 1] == '/')) {
        if (lex->src[lex->pos] == '\n')
            lex->line++;
        lex->pos++;
    }
    if (lex->src[lex->pos])
        lex->pos += 2;
}

void skip_ws_comments(lexer_t *lex)
{
    while (lex->src[lex->pos]) {
        if (lex->src[lex->pos] == '\n') {
            lex->line++;
            lex->pos++;
        } else if (lex->src[lex->pos] == ' ' ||
            lex->src[lex->pos] == '\t' ||
            lex->src[lex->pos] == '\r') {
            lex->pos++;
        } else if (lex->src[lex->pos] == '/' &&
            lex->src[lex->pos + 1] == '/') {
            skip_line_comment(lex);
        } else if (lex->src[lex->pos] == '/' &&
            lex->src[lex->pos + 1] == '*') {
            skip_block_comment(lex);
        } else {
            break;
        }
    }
}

void lex_double_char(lexer_t *lex)
{
    char a = lex->src[lex->pos];
    char b = lex->src[lex->pos + 1];

    if (a == '=' && b == '=') { lex_add(lex, TOK_EQEQ, "==", 0); lex->pos += 2; return; }
    if (a == '!' && b == '=') { lex_add(lex, TOK_NE, "!=", 0); lex->pos += 2; return; }
    if (a == '<' && b == '=') { lex_add(lex, TOK_LE, "<=", 0); lex->pos += 2; return; }
    if (a == '>' && b == '=') { lex_add(lex, TOK_GE, ">=", 0); lex->pos += 2; return; }
    if (a == '&' && b == '&') { lex_add(lex, TOK_AND, "&&", 0); lex->pos += 2; return; }
    if (a == '|' && b == '|') { lex_add(lex, TOK_OR, "||", 0); lex->pos += 2; return; }
    lex_op(lex);
}

void lex_op(lexer_t *lex)
{
    char c = lex->src[lex->pos];
    char next = lex->src[lex->pos + 1];
    char buf[3] = {c, '\0', '\0'};

    if ((c == '=' || c == '!' || c == '<' || c == '>') && next == '=') {
        lex_double_char(lex);
        return;
    }
    if ((c == '&' && next == '&') || (c == '|' && next == '|')) {
        lex_double_char(lex);
        return;
    }
    lex->pos++;
    if (c == '=') lex_add(lex, TOK_EQ, buf, 0);
    else if (c == '+') lex_add(lex, TOK_PLUS, buf, 0);
    else if (c == '-') lex_add(lex, TOK_MINUS, buf, 0);
    else if (c == '*') lex_add(lex, TOK_MUL, buf, 0);
    else if (c == '/') lex_add(lex, TOK_DIV, buf, 0);
    else if (c == '%') lex_add(lex, TOK_MOD, buf, 0);
    else if (c == '<') lex_add(lex, TOK_LT, buf, 0);
    else if (c == '>') lex_add(lex, TOK_GT, buf, 0);
    else if (c == '!') lex_add(lex, TOK_NOT, buf, 0);
    else if (c == ';') lex_add(lex, TOK_SEMI, buf, 0);
    else if (c == ',') lex_add(lex, TOK_COMMA, buf, 0);
    else if (c == '(') lex_add(lex, TOK_LPAREN, buf, 0);
    else if (c == ')') lex_add(lex, TOK_RPAREN, buf, 0);
    else if (c == '{') lex_add(lex, TOK_LBRACE, buf, 0);
    else if (c == '}') lex_add(lex, TOK_RBRACE, buf, 0);
    else {
        fprintf(stderr, "Unknown character '%c' at line %d\n",
            c, lex->line);
    }
}
