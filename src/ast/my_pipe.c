/*
** EPITECH PROJECT, 2025
** teksh
** File description:
** my_pipe
*/

#include "parser.h"
#include "mysh.h"

int first_child_proc(pid_t pid1, int pipefd[2], ast_t *left, mysh_t *mysh)
{
    if (pid1 == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        bt_exec(left, mysh);
        exit(0);
    }
    return 0;
}

int second_child_proc(pid_t pid1, int pipefd[2], ast_t *right,
    mysh_t *mysh)
{
    close(pipefd[1]);
    dup2(pipefd[0], 0);
    close(pipefd[0]);
    mysh->status = bt_exec(right, mysh);
    waitpid(pid1, NULL, 0);
    return mysh->status;
}

void restore_fd(int save_stdin, int save_stdout)
{
    dup2(save_stdin, 0);
    dup2(save_stdout, 1);
    close(save_stdin);
    close(save_stdout);
}

int pipe_func(ast_t *root, mysh_t *mysh)
{
    int pipefd[2] = {0};
    pid_t pid1 = 0;
    int save_stdin = dup(0);
    int save_stdout = dup(1);

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return 84;
    }
    first_child_proc(pid1, pipefd, root->left, mysh);
    if (pid1 != 0) {
        mysh->status = second_child_proc(pid1, pipefd, root->right, mysh);
        restore_fd(save_stdin, save_stdout);
    }
    return mysh->status;
}
