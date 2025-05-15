/*
** EPITECH PROJECT, 2025
** teksh
** File description:
** free_node
*/

#include "parser.h"
#include <stdlib.h>

void free_node(ast_t *node)
{
    if (!node)
        return;
    if (node->cmd)
        free(node->cmd);
    free(node);
}

void bt_free(ast_t *root)
{
    if (!root)
        return;
    bt_free(root->left);
    bt_free(root->right);
    free_node(root);
}
