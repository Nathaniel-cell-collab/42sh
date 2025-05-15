/*
** EPITECH PROJECT, 2025
** teksh
** File description:
** ast_semicolon
*/

#include "parser.h"
#include "mysh.h"

int semicolon_func(ast_t *root, mysh_t *mysh)
{
    mysh->status = bt_exec(root->left, mysh);
    mysh->status = bt_exec(root->right, mysh);
    return mysh->status;
}
