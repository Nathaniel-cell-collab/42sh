/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** arr_info
*/

#include "header.h"

void get_arr_info(char **arr, int *len, size_t *size)
{
    if (!arr)
        return;
    while (arr[*len]) {
        *size += strlen(arr[*len]);
        (*len)++;
    }
}
