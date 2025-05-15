/*
** EPITECH PROJECT, 2025
** my_exit
** File description:
** exit minishell
*/

#include <stdlib.h>
#include "mysh.h"
#include "struct_mysh.h"

char **my_builtin(char **command, mysh_t *mysh, int *exec)
{
    int status = mysh->status;

    if (!command || !(*command))
        return mysh->env;
    if (strcmp(*command, "exit") == 0) {
        my_free_array(command);
        free_shell(mysh);
        exit(status);
    }
    for (int i = 0; BUILTIN_FUNCS[i].name; i++) {
        if (strcmp(*command, BUILTIN_FUNCS[i].name) == 0) {
            *exec = 1;
            BUILTIN_FUNCS[i].func(mysh, command);
        }
    }
    return mysh->env;
}
