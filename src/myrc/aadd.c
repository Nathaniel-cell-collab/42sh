/*
** EPITECH PROJECT, 2025
** mysh
** File description:
** aad
*/
#include "myrc.h"
#include "mysh.h"
#include "my_free.h"

char *get_usr_clean(alias_t **alias, char *user_alias)
{
    char **tab = NULL;
    char *user_clean = NULL;

    if (!alias || !user_alias)
        return NULL;
    tab = word_array(user_alias, " \n");
    if (!tab)
        exit(84);
    user_clean = clean_str(tab[1]);
    my_free_array(tab);
    return user_clean;
}

int get_index_alias(alias_t **alias, char *user_alias)
{
    char *alias_cleaned = NULL;
    char *user_cleaned = get_usr_clean(alias, user_alias);
    int index = -1;

    if (!user_cleaned)
        return -1;
    for (int i = 0; alias[i] != NULL; i++) {
        alias_cleaned = clean_str(alias[i]->old_cmd);
        if (!alias_cleaned)
            exit(84);
        if (strcmp(alias_cleaned, user_cleaned) == 0)
            index = i;
        my_free(&alias_cleaned);
    }
    my_free(&user_cleaned);
    return index;
}

alias_t **append_alias(char *line, alias_t **alias)
{
    char **tab = word_array(line, " \n");
    int len = count_alias(alias);

    if (!tab)
        exit(84);
    alias = realloc(alias, sizeof(alias_t *) * (len + 2));
    if (!alias)
        exit(84);
    tab[1] = without_quotes(tab[1]);
    tab[2] = without_quotes(tab[2]);
    alias[len] = init_alias(tab[2], tab[1]);
    alias[len + 1] = NULL;
    my_free(&tab[0]);
    for (int i = 3; tab[i] != NULL; i++)
        my_free(&tab[i]);
    my_free(&tab);
    return alias;
}

alias_t **change_alias(alias_t **alias, int i, char *line)
{
    char **tab = word_array(line, " \n");

    my_free(&alias[i]->new_cmd);
    tab[2] = without_quotes(tab[2]);
    alias[i]->new_cmd = tab[2];
    for (int j = 0; tab[j] != NULL; j++)
        if (j != 2)
            my_free(&tab[j]);
    my_free(&tab);
    return alias;
}

alias_t **aadd(char *line, alias_t **alias)
{
    int i = 0;

    if (!alias) {
        alias = xcalloc(1, sizeof(alias_t *));
        return append_alias(line, alias);
    }
    i = get_index_alias(alias, line);
    if (i == -1)
        return append_alias(line, alias);
    return change_alias(alias, i, line);
}
