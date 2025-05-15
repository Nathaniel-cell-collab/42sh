/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** init_env
*/

#include "mysh.h"

char **init_env(char **env)
{
    return cpy_env_and_add(env, 0, NULL);
}
