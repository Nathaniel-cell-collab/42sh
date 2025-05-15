/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** which
*/

#include "../../include/mysh.h"

bool is_bt(char *command)
{
    for (int i = 0; BUILTIN_FUNCS[i].name; i++) {
        if (strcmp(command, BUILTIN_FUNCS[i].name) == 0) {
            return true;
        }
    }
    return false;
}

char **my_which(mysh_t *mysh, char **command)
{
    char *path = NULL;

    for (int i = 1; command[i]; i++) {
        path = find_full_path(command + i, mysh->env);
        if (is_bt(command[i])) {
            printf("%s: shell built-in command.\n", command[i]);
            continue;
        }
        if (!path)
            printf("%s: Command not existing.\n", command[i]);
        else
            printf("%s\n", path);
    }
    my_free(&path);
    return mysh->env;
}
