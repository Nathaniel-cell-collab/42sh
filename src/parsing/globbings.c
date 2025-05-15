/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** globbings
*/

#include "../include/mysh.h"

int is_glob(const char *s)
{
    return (strchr(s, '*') || strchr(s, '?') || strchr(s, '['));
}

char **glob_detect(char *elem, char **new_arr, glob_t *glob_struct, int *count)
{
    if (glob(elem, 0, NULL, glob_struct) == 0) {
        for (size_t j = 0; j < glob_struct->gl_pathc; j++) {
            new_arr = my_push_tab(new_arr, glob_struct->gl_pathv[j]);
            (*count)++;
        }
    } else {
        new_arr = my_push_tab(new_arr, elem);
        (*count)++;
    }
    globfree(glob_struct);
    return new_arr;
}

int handle_globbings(mysh_t *mysh)
{
    char **array = word_array(mysh->nline, " \n");
    glob_t *glob_struct = calloc(1, sizeof(glob_t));
    char **new_arr = calloc(1, sizeof(char *));
    int count = 0;

    for (int i = 0; array[i]; i++) {
        if (is_glob(array[i])) {
            new_arr = glob_detect(array[i], new_arr, glob_struct, &count);
            continue;
        }
        new_arr = my_push_tab(new_arr, array[i]);
        count++;
    }
    my_free(&(mysh->nline));
    mysh->nline = array_to_str(new_arr);
    my_free_array(array);
    my_free_array(new_arr);
    globfree(glob_struct);
    my_free(&glob_struct);
    return 0;
}
