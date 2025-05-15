/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** set
*/

#include "mysh.h"

char **my_set(mysh_t *mysh, char **command)
{
    mysh->local_env = my_set_var(mysh->local_env, command, "set");
    return mysh->env;
}
