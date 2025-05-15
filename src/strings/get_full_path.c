/*
** EPITECH PROJECT, 2025
** get_full_path
** File description:
** get the full_path of a command
*/

#include "my_strings.h"
#include "my_free.h"

char *get_full_path(char *dir, char *exec)
{
    char *full_path = NULL;

    if (!dir || !exec)
        return NULL;
    full_path = xcalloc((strlen(dir) +
    strlen(exec) + 2), sizeof(char));
    full_path = strcpy(full_path, dir);
    full_path = strcat(full_path, "/");
    full_path = strcat(full_path, exec);
    return full_path;
}
