/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** unsetenv
*/

#include "mysh.h"

char **my_copy_env_and_del(char **env, char *command)
{
    char **new_env = NULL;
    int i = 0;
    int j = 0;

    new_env = xcalloc((my_len_array(env)), sizeof(char *));
    if (!command || !env)
        return NULL;
    for (i = 0; env[i]; i++) {
        if (strncmp(command, env[i], strlen(command)) == 0)
            continue;
        new_env[j] = xstrdup(env[i]);
        if (!new_env[j])
            return NULL;
        j++;
    }
    new_env[j] = NULL;
    my_free_array(env);
    return new_env;
}

char **my_unset_var(char **old_env, char **command)
{
    char *var_env = NULL;
    char **new_env = old_env;

    if (!old_env)
        return old_env;
    for (int i = 1; command[i]; i++) {
        var_env = my_get_env(old_env, command[i]);
        if (!var_env)
            continue;
        new_env = my_copy_env_and_del(old_env, command[i]);
        old_env = new_env;
    }
    return new_env;
}

char **my_unsetenv(mysh_t *mysh, char **command)
{
    mysh->env = my_unset_var(mysh->env, command);
    return mysh->env;
}
