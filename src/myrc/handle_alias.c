/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** main
*/

#include "../include/mysh.h"

int verif_alias(mysh_t *mysh, char *line, alias_t **alias)
{
    char **tab = line && *line ? word_array(line, " \n") : NULL;
    bool is_alias = tab ? strcmp(tab[0], "alias") == 0 : 0;

    if (!tab)
        return 0;
    if (!is_alias ||
        (my_len_array(tab) != 1 && my_len_array(tab) != 3)) {
        my_free_array(tab);
        return is_alias;
    }
    if (my_len_array(tab) == 1) {
        dump_alias(mysh->alias);
        my_free_array(tab);
        return 1;
    }
    mysh->alias = aadd(line, alias);
    my_free_array(tab);
    return 1;
}

int verif_unalias(mysh_t *mysh, char *line)
{
    char **tab = line && *line ? word_array(line, " \n") : NULL;

    if (!tab)
        return 0;
    if (!*tab || strcmp(tab[0], "unalias") != 0) {
        my_free_array(tab);
        return 0;
    }
    if (my_len_array(tab) == 1) {
        dprintf(2, "unalias: Too few arguments.\n");
        my_free_array(tab);
        return 1;
    }
    if (!(mysh->alias) || !*(mysh->alias)) {
        my_free_array(tab);
        return 1;
    }
    mysh->alias = unalias(line, mysh->alias);
    my_free_array(tab);
    return 1;
}

int handle_alias(mysh_t *mysh)
{
    char **tab = mysh->nline && *(mysh->nline) ?
        word_array(mysh->nline, " \n") : NULL;
    alias_t **aliases = mysh->alias;

    if (!tab)
        return 0;
    for (int i = 0; aliases && aliases[i]; i++) {
        if (strcmp(tab[0], aliases[i]->old_cmd) == 0) {
            my_free(&tab[0]);
            tab[0] = strdup(aliases[i]->new_cmd);
            break;
        }
    }
    my_free(&(mysh->nline));
    mysh->nline = array_to_str(tab);
    my_free_array(tab);
    return 0;
}
