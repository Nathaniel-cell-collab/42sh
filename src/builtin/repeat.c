/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** which
*/

#include "../../include/mysh.h"

char **my_repeat(mysh_t *mysh, char **command)
{
    int nb = 0;

    if (my_len_array(command) != 3) {
        dprintf(2, "repeat: Bad arguments.\n");
        return mysh->env;
    }
    for (int i = 0; command[1][i]; i++)
        if (!isdigit(command[1][i])) {
            dprintf(2, "repeat: Badly formed number.\n");
            return mysh->env;
        }
    nb = atoi(command[1]);
    for (int i = 0; i < nb; i++)
        exec_sh(mysh, command[2]);
    return mysh->env;
}
