/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** len_array
*/

#include "my_strings.h"

int my_len_array(char **array)
{
    int i = 0;

    if (!array)
        return -1;
    while (array[i] != NULL)
        i++;
    return i;
}
