/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** my_unset
*/

#include "mysh.h"

char **my_unset(mysh_t *mysh, char **command)
{
    mysh->local_env = my_unset_var(mysh->local_env, command);
    return mysh->env;
}
