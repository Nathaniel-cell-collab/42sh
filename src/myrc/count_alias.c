/*
** EPITECH PROJECT, 2025
** mysh
** File description:
** aad
*/
#include "myrc.h"
#include "mysh.h"
#include "my_free.h"

int count_alias(alias_t **alias)
{
    int count = 0;

    if (!alias)
        return 0;
    while (alias[count] != NULL)
        count++;
    return count;
}
