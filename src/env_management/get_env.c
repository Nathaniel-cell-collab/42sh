/*
** EPITECH PROJECT, 2025
** my_get_env
** File description:
** recreate getenv
*/

#include "mysh.h"

char *my_get_env(char **env, char *var_env)
{
    char *path_env = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        if (strncmp(env[i], var_env, strlen(var_env)) == 0)
            path_env = env[i] + strlen(var_env);
    }
    return path_env;
}
