/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** get_error
*/

#include "mysh.h"

void get_error(int err, char *command)
{
    if (err == 13) {
        dprintf(2, BAD_PERM, command);
        return;
    }
    if (err == 8) {
        dprintf(2, EXEC_FORMAT, command);
        return;
    }
}
