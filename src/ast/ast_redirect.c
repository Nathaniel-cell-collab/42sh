/*
** EPITECH PROJECT, 2025
** teksh
** File description:
** ast_redirect
*/

#include "parser.h"
#include "mysh.h"

int output_redirect(pid_t pid1, int fd, ast_t *left, mysh_t *mysh)
{
    int res = 0;

    if (pid1 == 0) {
        dup2(fd, 1);
        res = bt_exec(left, mysh);
        exit(WEXITSTATUS(res));
    }
    return res;
}

int call_ast(pid_t pid1, ast_t *right, mysh_t *mysh)
{
    waitpid(pid1, &(mysh->status), 0);
    if (mysh->status)
        return mysh->status;
    mysh->status = bt_exec(right, mysh);
    return mysh->status;
}

char *search_file(char *ptr)
{
    int i = 0;
    char *filepath = NULL;

    if (!strlen(ptr))
        return NULL;
    ptr = skip_char(ptr, " \t");
    for (i = 0; ptr[i]; i++) {
        if (';' == ptr[i] || ptr[i] == 32)
            break;
    }
    if (i == 0)
        return NULL;
    filepath = strndup(ptr, i);
    return filepath;
}

static int verif_redirect(ast_t *root)
{
    if (root->type == PIPE || root->type == S_REDIRECT_OUT ||
        root->type == 4) {
        dprintf(2, "Ambiguous output redirect.\n");
        return 0;
    }
    return 1;
}

int redirect_output(int fd, ast_t *left, ast_t *right, mysh_t *mysh)
{
    pid_t pid1 = 0;
    int save_stdin = dup(0);
    int save_stdout = dup(1);

    if (fd == -1)
        return 84;
    pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        return 84;
    }
    output_redirect(pid1, fd, left, mysh);
    if (pid1 != 0) {
        mysh->status = call_ast(pid1, right->right, mysh);
        restore_fd(save_stdin, save_stdout);
    }
    return mysh->status;
}

int redirect_out_func(ast_t *root, mysh_t *mysh)
{
    char *filepath = search_file(root->right->cmd);
    int fd = 0;

    if (!filepath)
        return 84;
    if (!verif_redirect(root->right))
        return 84;
    if (root->type == S_REDIRECT_OUT)
        fd = open(filepath, O_CREAT | O_TRUNC | O_WRONLY, 00664);
    if (root->type == D_REDIRECT_OUT)
        fd = open(filepath, O_CREAT | O_APPEND | O_WRONLY, 00664);
    if (redirect_output(fd, root->left, root->right, mysh)) {
        my_free(&filepath);
        return mysh->status;
    }
    close(fd);
    my_free(&filepath);
    return 0;
}
