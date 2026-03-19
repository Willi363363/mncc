/*
** EPITECH PROJECT, 2026
** parse_block.c
** File description:
** Block instruction parsing function
*/
#include <errno.h>
#include "lexer/token.h"
#include "main.h"
#include "parser/node.h"
#include "parser/parser.h"
#include "utils/utils.h"

static int handle_instruction(parser_t *parser, node_t *block_node)
{
    node_t *instruction = parse_instruction(parser);

    if (!instruction) {
        node_destroy(block_node);
        return ERROR;
    }
    if (array_push(block_node->childs, instruction) == ERROR) {
        node_destroy(instruction);
        node_destroy(block_node);
        get_error(ENOMEM, "parser block instruction implementation");
        return ERROR;
    }
    return SUCCESS;
}

node_t *parse_block(parser_t *parser)
{
    node_t *node = node_create(NODE_BLOCK);
    bool one_line = false;

    if (!node) {
        get_error(ENOMEM, "parser block node allocation");
        return NULL;
    }
    if (parser_match(parser, TOK_LBRACE))
        parser->cursor++;
    else
        one_line = true;
    for (int i = 0; !parser_match(parser, TOK_RBRACE) && (!one_line || i == 0);
        i++) {
        if (handle_instruction(parser, node) != SUCCESS)
            return NULL;
    }
    if (!one_line)
        parser->cursor++;
    return node;
}
