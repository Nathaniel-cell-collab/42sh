/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-minishell2-nathaniel.leperlier
** File description:
** get_file_content
*/

#include "parser.h"
#include "mysh.h"

int input_redirect(pid_t pid1, int fd, ast_t *left, mysh_t *mysh)
{
    int res = 0;

    if (pid1 == 0) {
        dup2(fd, 0);
        res = bt_exec(left, mysh);
        exit(WEXITSTATUS(res));
    }
    return 0;
}

int redirect_input(int fd, ast_t *left, ast_t *right, mysh_t *mysh)
{
    pid_t pid1 = 0;
    int save_stdin = dup(0);
    int save_stdout = dup(1);
    int res = 0;

    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return 84;
    }
    input_redirect(pid1, fd, left, mysh);
    if (pid1 != 0) {
        res = call_ast(pid1, right->right, mysh);
        restore_fd(save_stdin, save_stdout);
    }
    return res;
}

int redirect_in_func(ast_t *root, mysh_t *mysh)
{
    char *filepath = search_file(root->right->cmd);
    int fd = 0;

    if (!filepath)
        return 84;
    fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("open");
        my_free(&filepath);
        return 84;
    }
    mysh->status = redirect_input(fd, root->left, root->right, mysh);
    close(fd);
    my_free(&filepath);
    return mysh->status;
}
