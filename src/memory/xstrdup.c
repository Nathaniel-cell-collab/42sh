/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** xstrdup
*/

#include "header.h"

char *xstrdup(const char *str)
{
    char *ptr = strdup(str);

    if (!ptr) {
        perror("malloc");
        exit(84);
    }
    return ptr;
}
