/*
** EPITECH PROJECT, 2025
** create_alias
** File description:
** mysh
*/
#include "myrc.h"
#include "mysh.h"

void add_alias(char *old, char *new)
{
    int fd = open(RC_FILE, O_WRONLY | O_CREAT | O_APPEND, 00644);

    if (fd == -1)
        return;
    if (!old || !new)
        return;
    dprintf(fd, "alias %s='%s'\n", new, old);
    close(fd);
}
