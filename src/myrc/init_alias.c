/*
** EPITECH PROJECT, 2025
** create_alias
** File description:
** mysh
*/
#include "myrc.h"
#include "mysh.h"

alias_t *init_alias(char *new, char *old)
{
    alias_t *alias = xcalloc(1, sizeof(alias_t));

    if (!alias || !new || !old)
        exit(84);
    alias->old_cmd = old;
    alias->new_cmd = new;
    return alias;
}
