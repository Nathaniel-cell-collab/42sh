/*
** EPITECH PROJECT, 2025
** teksh
** File description:
** pretty_printer
*/

#include "parser.h"
#include "mysh.h"

int bt_exec(ast_t *root, mysh_t *mysh)
{
    if (!root)
        return 0;
    if (root->type == CMD) {
        mysh->status = exec_sh(mysh, root->cmd);
        push_sate(mysh);
        return mysh->status;
    }
    for (int i = 0; OP_TAB[i].op; i++) {
        if (root->type == OP_TAB[i].type) {
            mysh->status = OP_TAB[i].func(root, mysh);
            return mysh->status;
        }
    }
    return 84;
}
