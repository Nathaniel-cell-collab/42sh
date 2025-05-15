/*
** EPITECH PROJECT, 2025
** teksh
** File description:
** clean_str
*/

#include "my_free.h"
#include "my_strings.h"

char *clean_str(char *str)
{
    char *cpy_str = NULL;
    char *clean_str = NULL;

    if (!str)
        return NULL;
    cpy_str = xstrdup(str);
    clean_str = xstrdup(skip_char(cpy_str, " \t"));
    if (my_str_change_char(clean_str, "\t", 32) == NULL) {
        my_free(&cpy_str);
        my_free(&clean_str);
        return NULL;
    }
    my_str_change_char(clean_str, "\n", 0);
    my_free(&cpy_str);
    return clean_str;
}
