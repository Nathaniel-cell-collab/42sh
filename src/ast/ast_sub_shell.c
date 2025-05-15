/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** ast_sub_shell
*/

#include "mysh.h"

int ast_subshell(ast_t *root, mysh_t *mysh)
{
    pid_t pid = 0;
    int status = 0;
    mysh_t *dupsh = init_shell(mysh->env);

    dupsh->line = xstrdup(root->left->cmd);
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(84);
    }
    if (pid == 0) {
        status = loop(dupsh);
        exit(status);
    }
    waitpid(pid, &status, 0);
    free_shell(dupsh);
    return status;
}
