/*
** EPITECH PROJECT, 2025
** B-CPE-200-RUN-2-1-amazed-nathaniel.leperlier
** File description:
** my_realloc
*/

#include "mysh.h"

char **my_push_tab(char **src, char *to_push)
{
    char **new_array = NULL;
    int i = 0;

    if (!to_push)
        return src;
    new_array = calloc(sizeof(char *), (my_len_array(src) + 2));
    if (!new_array)
        exit(84);
    while (src[i] != NULL) {
        new_array[i] = strdup(src[i]);
        if (!new_array[i])
            exit(84);
        i = i + 1;
    }
    new_array[i] = strdup(to_push);
    if (!new_array[i])
            exit(84);
    new_array[i + 1] = NULL;
    my_free_array(src);
    return new_array;
}
