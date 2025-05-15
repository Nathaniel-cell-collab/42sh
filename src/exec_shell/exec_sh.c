/*
** EPITECH PROJECT, 2025
** main
** File description:
** main func of minishell
*/

#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "mysh.h"
#include <errno.h>

void sig_exec(char *full_path, mysh_t *mysh, char **command)
{
    restore_sig();
    if (execve(full_path, command, mysh->env) == -1){
        get_error(errno, *command);
    }
}

int try_command(char **command, mysh_t *mysh)
{
    char *full_path = find_full_path(command, mysh->env);
    pid_t pid = 0;
    int status = 0;

    if (!full_path) {
        dprintf(2, BAD_CMD, *command);
        return 84;
    }
    pid = fork();
    if (pid == 0) {
        sig_exec(full_path, mysh, command);
        exit(1);
    }
    waitpid(pid, &status, 0);
    if (WTERMSIG(status) != 0)
        dprintf(2, "%s\n", strsignal(WTERMSIG(status)));
    free(full_path);
    return status;
}

int my_command(mysh_t *mysh, char **command)
{
    int exec = 0;
    int status = 0;

    if (!(*command))
        return 84;
    mysh->env = my_builtin(command, mysh, &exec);
    if (!(mysh->env)) {
        my_free_array(command);
        exit(84);
    }
    if (exec == 0)
        status = try_command(command, mysh);
    return status;
}

char *format_line(mysh_t *mysh, char *line)
{
    int len = strlen(line);

    if (mysh->nline)
        my_free(&(mysh->nline));
    mysh->nline = xcalloc(len + 2, sizeof(char));
    memcpy(mysh->nline, line, len);
    lget_cmd(mysh);
    hget_cmd(mysh);
    handle_alias(mysh);
    handle_back(mysh);
    handle_globbings(mysh);
    return mysh->nline;
}

int exec_sh(mysh_t *mysh, char *line)
{
    char **command = NULL;
    int status = 0;

    line = format_line(mysh, line);
    line = my_str_change_char(line, "\t", ' ');
    command = word_array(line, " ");
    if (!command)
        exit(84);
    for (int i = 0; command[i]; i++)
    command[i] = without_quotes(command[i]);
    status = my_command(mysh, command);
    my_free_array(command);
    my_free(&mysh->nline);
    return status;
}
