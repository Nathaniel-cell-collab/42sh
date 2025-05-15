/*
** EPITECH PROJECT, 2025
** create_alias
** File description:
** mysh
*/
#include "myrc.h"
#include "mysh.h"

alias_t **load_alias(void)
{
    alias_t **aliases = NULL;
    FILE *myrc = fopen(RC_FILE, "r");
    char *line = NULL;
    size_t n = 0;
    char **tab = NULL;

    if (!myrc)
        return NULL;
    while (getline(&line, &n, myrc) > 0) {
        tab = word_array(line, " \n");
        if (my_len_array(tab) == 3 && strcmp(tab[0], "alias") == 0)
            aliases = aadd(line, aliases);
        my_free_array(tab);
    }
    my_free(&line);
    fclose(myrc);
    return aliases;
}
