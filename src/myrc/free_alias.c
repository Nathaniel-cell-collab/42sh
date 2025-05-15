/*
** EPITECH PROJECT, 2025
** free
** File description:
** alias
*/
#include "myrc.h"
#include "my_free.h"
void free_array_alias(alias_t **alias)
{
    if (!alias)
        return;
    for (int i = 0; alias[i] != NULL; i++)
        free_alias(alias[i]);
    my_free(&alias);
}

void free_alias(alias_t *alias)
{
    my_free(&(alias->old_cmd));
    my_free(&(alias->new_cmd));
    my_free(&alias);
}
