/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** my_and
*/

#include "parser.h"
#include "mysh.h"

int ast_and(ast_t *root, mysh_t *mysh)
{
    mysh->status = bt_exec(root->left, mysh);
    return mysh->status != 0 ? mysh->status : bt_exec(root->right, mysh);
}
