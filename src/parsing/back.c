/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** back
*/

#include "mysh.h"

int run_cmd(int pipefd[2], mysh_t *mysh, char *cmd)
{
    pid_t pid = 0;
    int status = 0;
    mysh_t *dupsh = init_shell(mysh->env);

    dupsh->line = xstrdup(cmd);
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(84);
    }
    if (pid == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        status = loop(dupsh);
        exit(WEXITSTATUS(status));
    }
    close(pipefd[1]);
    waitpid(pid, &status, 0);
    free_shell(dupsh);
    return status;
}

static char *fill_buf(int pipefd[2], char *result)
{
    char buffer[1024] = {0};
    ssize_t len = 0;

    len = read(pipefd[0], buffer, 1024);
    while (len > 0) {
        result = realloc(result, (len + strlen(result) + 1) * sizeof(char));
        if (!result)
            exit(84);
        result = strcat(result, buffer);
        len = read(pipefd[0], buffer, 1024);
    }
    close(pipefd[0]);
    return result;
}

char *get_output(char *cmd, mysh_t *mysh)
{
    int pipefd[2] = {0};
    char *result = xcalloc(1, sizeof(char));

    if (pipe(pipefd) == -1)
        return NULL;
    if (run_cmd(pipefd, mysh, cmd)) {
        my_free(&result);
        return NULL;
    }
    result = fill_buf(pipefd, result);
    close(pipefd[0]);
    return result;
}

char *get_under_back(char *line, int *size)
{
    int i = 0;
    char *str = NULL;

    if (line[i] != '`')
        return NULL;
    i++;
    while (line[i] != '`') {
        i++;
    }
    *size = i;
    str = my_strndup(line, 1, i - 1);
    return str;
}

char *bget_new_cmd(char *cmd, int size, char *output)
{
    char *new_cmd = xcalloc(strlen(cmd) - size +
    strlen(output), sizeof(char *));
    int i = 0;
    int j = 0;

    while (cmd[i]) {
        if (cmd[i] == '`') {
            new_cmd = strcat(new_cmd, output);
            i += size + 1;
            j += strlen(output);
            continue;
        }
        new_cmd[j] = cmd[i];
        i++;
        j++;
    }
    new_cmd = my_str_change_char(new_cmd, "\n", ' ');
    my_free(&cmd);
    return new_cmd;
}

int handle_back(mysh_t *mysh)
{
    int size = 0;
    char *str = NULL;
    char *output = NULL;

    for (int i = 0; mysh->nline[i]; i++) {
        str = get_under_back(mysh->nline + i, &size);
        if (!str)
            continue;
        output = get_output(str, mysh);
        my_free(&str);
        if (!output || !output[0])
            continue;
        mysh->nline = bget_new_cmd(mysh->nline, size, output);
        my_free(&output);
        i += size;
    }
    return 0;
}
