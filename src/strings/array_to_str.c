/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** array_to_str
*/

#include "../include/mysh.h"

char *array_to_str(char **array)
{
    char *str = NULL;
    size_t total_size = 1;

    for (int i = 0; array[i]; i++) {
        total_size += strlen(array[i]) + 1;
    }
    str = xcalloc(total_size, sizeof(char));
    for (int i = 0; array[i]; i++) {
        strcat(str, array[i]);
        if (array[i + 1])
            strcat(str, " ");
    }
    return str;
}
