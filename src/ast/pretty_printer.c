/*
** EPITECH PROJECT, 2025
** teksh
** File description:
** pretty_printer
*/

#include "parser.h"
#include "mysh.h"

void bt_pprint(ast_t *root)
{
    if (!root)
        return;
    bt_pprint(root->left);
    if (root->type == CMD) {
        printf("CMD: %s\n", root->cmd);
    }
    bt_pprint(root->right);
    for (int i = 0; OP_TAB[i].op; i++) {
        if (root->type == OP_TAB[i].type) {
            printf("OP: %s\n", OP_TAB[i].op);
        }
    }
}
