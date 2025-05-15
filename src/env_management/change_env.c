/*
** EPITECH PROJECT, 2025
** gg
** File description:
** gg
*/

#include "mysh.h"

char **init_pwd_env(char *pathname, char *var_env)
{
    char **pwd = malloc(sizeof(char *) * (5));

    if (!pwd)
        exit(84);
    for (int i = 0; i < 5; i++)
        pwd[i] = 0;
    pwd[0] = strdup("cd");
    if (!pwd[0])
        exit(84);
    pwd[1] = strdup(var_env);
    if (!pwd[1])
        exit(84);
    pwd[2] = strdup(pathname);
    if (!pwd[2])
        exit(84);
    pwd[4] = NULL;
    return pwd;
}

void change_env(mysh_t *mysh, char *pathname, char *currpath, char **pwd)
{
        pwd = init_pwd_env(pathname, "PWD");
        mysh->env = my_setenv(mysh, pwd);
        my_free_array(pwd);
        pwd = init_pwd_env(currpath, "OLDPWD");
        mysh->env = my_setenv(mysh, pwd);
        my_free_array(pwd);
}
