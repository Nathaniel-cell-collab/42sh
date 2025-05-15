/*
** EPITECH PROJECT, 2025
** myrc
** File description:
** unalias
*/
#include "myrc.h"
#include "mysh.h"
#include "my_free.h"

alias_t *loop_alias(alias_t *alias, char **tab)
{
    alias_t *new_alias = NULL;

    for (int j = 1; tab[j] != NULL; j++)
        if (strcmp(alias->old_cmd, tab[j]) == 0) {
            free_alias(alias);
            return NULL;
        }
    new_alias = init_alias(strdup(alias->new_cmd), strdup(alias->old_cmd));
    free_alias(alias);
    return new_alias;
}

void check_realloc(alias_t **alias)
{
    if (!alias)
        exit(84);
}

alias_t **unalias(char *line, alias_t **alias)
{
    char **tab = word_array(line, " \n");
    alias_t **aliases = NULL;
    int i = 0;
    int len = 0;

    aliases = xcalloc(2, sizeof(alias_t *));
    while (alias[i] != NULL) {
        aliases[len] = loop_alias(alias[i], tab);
        if (aliases[len]) {
            len++;
            aliases = realloc(aliases, sizeof(alias_t *) * (len + 2));
            check_realloc(aliases);
            aliases[len + 1] = NULL;
        }
        i++;
    }
    my_free(&alias);
    my_free_array(tab);
    return aliases;
}
