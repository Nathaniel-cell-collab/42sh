/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** init_loc
*/

#include "my_free.h"

char **init_loc(void)
{
    char **new_env = xcalloc(2, sizeof(char *));

    new_env[0] = xstrdup("?=0");
    new_env[1] = NULL;
    return new_env;
}
