/*
** EPITECH PROJECT, 2025
** find_full_path
** File description:
** find a full path of a command
*/

#include "mysh.h"

char *try_full_path(char *dir, char *full_path, char **command)
{
    while (dir) {
        full_path = get_full_path(dir, *command);
        if (!full_path)
            return NULL;
        if (access(full_path, F_OK) == 0)
            return full_path;
        free(full_path);
        dir = strtok(NULL, ":");
    }
    return NULL;
}

char *find_full_path(char **command, char **env)
{
    char *path_env = my_get_env(env, "PATH=");
    char *dup_path = NULL;
    char *dir = NULL;
    char *full_path = NULL;

    if (!access(*command, F_OK) && !access(*command, X_OK))
        return xstrdup(*command);
    if (!path_env)
        return NULL;
    dup_path = xstrdup(path_env);
    dir = strtok(dup_path, ":");
    full_path = try_full_path(dir, full_path, command);
    free(dup_path);
    return full_path;
}
