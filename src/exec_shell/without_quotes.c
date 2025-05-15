/*
** EPITECH PROJECT, 2025
** main
** File description:
** main func of minishell
*/

#include <unistd.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "mysh.h"
#include <errno.h>

char *without_quotes(char *str)
{
    char *new_str = NULL;

    if (*str == '\'' || *str == '\'')
        new_str = strdup(str + 1);
    if (!new_str)
        return str;
    my_free(&str);
    if (new_str[strlen(new_str) - 1] == '\'')
        new_str[strlen(new_str) - 1] = '\0';
    return new_str;
}
