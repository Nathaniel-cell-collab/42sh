/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** setenv
*/

#include "mysh.h"

char **cpy_env_and_add(char **env, int resize, char *element)
{
    char **new_env = xcalloc(((my_len_array(env) + 1)) +
    (sizeof(char *) * resize), sizeof(char *));
    int i = 0;

    if (!env)
        return NULL;
    for (i = 0; env[i]; i++) {
        new_env[i] = xstrdup(env[i]);
    }
    if (resize > 0) {
        new_env[i] = my_str_change_char(xstrdup(element), " ", '=');
        i++;
    }
    new_env[i] = NULL;
    return new_env;
}

char **my_update_env(char **command, char **old_env, char *arg)
{
    char **new_env = NULL;

    for (int i = 0; old_env[i]; i++) {
        if (strncmp(command[1], old_env[i], strlen(command[1])) == 0) {
            my_free(&(old_env[i]));
            old_env[i] = my_str_change_char(xstrdup(arg), " ", '=');
            return old_env;
        }
    }
    new_env = cpy_env_and_add(old_env, 1, arg);
    my_free_array(old_env);
    return new_env;
}

int verif_setenv(char **arg, char **env, char *name)
{
    if ((arg[1]) == NULL) {
        print_tab(env);
        return 0;
    }
    if (my_len_array(arg) > 3)
        printf("%s: Too many arguments.\n", name);
    if (isdigit(arg[1][0])) {
        printf("%s: Variable name must begin with a letter.\n", name);
        return 0;
    }
    if (my_str_is_alphanum_and(arg[1], '_') == 0 && !strcmp("setenv", name)) {
        printf("%s: Variable name must contain ", name);
        printf("alphanumeric characters.\n");
        return 0;
    }
    return 1;
}

char **my_set_var(char **old_env, char **command, char *name)
{
    char *command2 = NULL;
    char *arg = NULL;
    char **new_env;

    if (!command || !old_env)
        return NULL;
    command2 = command[2];
    if (!command2)
        command2 = "";
    if (verif_setenv(command, old_env, name) == 0)
        return old_env;
    arg = xcalloc((strlen(command[1]) +
    strlen(command2) + 2), sizeof(char));
    arg = strcpy(arg, command[1]);
    strcat(arg, " ");
    strcat(arg, command2);
    new_env = my_update_env(command, old_env, arg);
    my_free(&arg);
    return new_env;
}

char **my_setenv(mysh_t *mysh, char **command)
{
    mysh->env = my_set_var(mysh->env, command, "setenv");
    return mysh->env;
}
