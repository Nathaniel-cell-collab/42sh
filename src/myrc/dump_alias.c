/*
** EPITECH PROJECT, 2025
** create_alias
** File description:
** mysh
*/
#include "myrc.h"
#include "mysh.h"

void dump_alias(alias_t **alias)
{
    if (!alias)
        return;
    for (int i = 0; alias[i]; i++)
        printf("%s\t(%s)\n", alias[i]->old_cmd, alias[i]->new_cmd);
}
