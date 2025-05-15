/*
** EPITECH PROJECT, 2024
** my_free
** File description:
** to free any pointer
*/

#include "header.h"

void my_free(void *ptr)
{
    void **pt = ptr;

    if (ptr && *pt)
        free(*pt);
    *pt = NULL;
}
