/*
** EPITECH PROJECT, 2026
** parser_print.c
** File description:
** Printing of parsed nodes for debugging purposes
*/
#include <stdio.h>
#include "parser/node.h"
#include "parser/parser.h"

static const node_debug_t node_debugs[] = {{NODE_FUNCTION, "FUNCTION"},
    {NODE_DECLARATION, "DECLARATION"},
    {NODE_ASSIGN, "ASSIGN"},
    {NODE_RETURN, "RETURN"},
    {NODE_BLOCK, "BLOCK"},
    {NODE_IF, "IF"},
    {NODE_OPERATOR, "OPERATOR"},
    {NODE_CALL, "CALL"},
    {NODE_VAR, "VAR"},
    {NODE_CONST, "CONST"},
    {NODE_NONE, NULL}};

static const char *node_type_to_string(node_type_t type)
{
    for (size_t i = 0; node_debugs[i].type != NODE_NONE; i++) {
        if (node_debugs[i].type == type)
            return node_debugs[i].name;
    }
    return "UNKNOWN";
}

static const char *operator_to_string(operator_type_t op)
{
    switch (op) {
        case OP_DEF:
            return "DEF";
        case OP_EQ:
            return "EQ";
        case OP_ADD:
            return "ADD";
        case OP_SUB:
            return "SUB";
        case OP_MUL:
            return "MUL";
        case OP_DIV:
            return "DIV";
        default:
            return "UNKNOWN";
    }
}

static void print_node_value(node_t *node, bool arrow)
{
    if (arrow)
        printf("-> ");
    if (node->type == NODE_CONST)
        printf("%s: val %d\n", node_type_to_string(node->type), node->value);
    else if (node->type == NODE_OPERATOR)
        printf("%s: %s\n",
            node_type_to_string(node->type),
            operator_to_string(node->op));
    else
        printf("%s: %s\n", node_type_to_string(node->type), node->name);
}

static void print_node(parser_t *parser, node_t *node, int indent, bool arrow)
{
    if (!node)
        return;
    for (int i = 0; i < indent; i++)
        printf("    ");
    print_node_value(node, arrow);
    if (node->left)
        print_node(parser, node->left, indent + 1, true);
    for (size_t i = 0; i < node->childs->count; i++) {
        print_node(parser, node->childs->data[i], indent + 1, false);
    }
    if (node->right)
        print_node(parser, node->right, indent + 1, true);
}

void parser_print(parser_t *parser)
{
    node_t *node = NULL;

    for (size_t i = 0; i < parser->nodes->count; i++) {
        node = parser->nodes->data[i];
        print_node(parser, node, 0, false);
    }
}
