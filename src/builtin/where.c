/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** which
*/

#include "../../include/mysh.h"
char **find_more_path(char **comm, char **env)
{
    char *path_env = my_get_env(env, "PATH=");
    char *dup_path = NULL;
    char **paths = xcalloc(1, sizeof(char *));
    char *stock = NULL;
    char *full_path = NULL;

    if (!path_env)
        return NULL;
    paths = !access(*comm, F_OK) ? my_push_tab(paths, *comm) : paths;
    dup_path = xstrdup(path_env);
    stock = strtok(dup_path, ":");
    for (int i = 0; i == 0 || paths[i - 1]; i++) {
        full_path = try_full_path(stock, paths[i], comm);
        paths = my_push_tab(paths, full_path);
        my_free(&full_path);
        stock = strtok(NULL, ":");
    }
    my_free(&dup_path);
    return paths;
}

char **my_where(mysh_t *mysh, char **command)
{
    char **path = NULL;
    bool bt = false;

    if (!command[1])
        printf("where: too few arguments.\n");
    for (int i = 1; command[i]; i++) {
        bt = is_bt(command[i]);
        path = find_more_path(command + i, mysh->env);
        if (bt)
            printf("%s: shell built-in command.\n", command[i]);
        if ((!path || !*path) && !bt)
            printf("%s: Command not existing.\n", command[i]);
        else
            print_tab(path);
        my_free_array(path);
    }
    return mysh->env;
}
