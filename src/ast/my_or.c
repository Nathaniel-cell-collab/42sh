/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** my_or
*/

#include "parser.h"
#include "mysh.h"

int ast_or(ast_t *root, mysh_t *mysh)
{
    return bt_exec(root->left, mysh) == 0 ? 0 : bt_exec(root->right, mysh);
}
