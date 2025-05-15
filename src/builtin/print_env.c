/*
** EPITECH PROJECT, 2025
** print_evn
** File description:
** print env
*/

#include "mysh.h"

char **print_env(mysh_t *mysh)
{
    print_tab(mysh->env);
    return mysh->env;
}
