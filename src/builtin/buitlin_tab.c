/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** buitlin_tab
*/

#include "mysh.h"
#include "history.h"

const struct builtin_s BUILTIN_FUNCS[] = {
    {"setenv", &my_setenv},
    {"unsetenv", &my_unsetenv},
    {"env", &print_env},
    {"cd", &change_dir},
    {"history", &dump_history},
    {"set", &my_set},
    {"unset", &my_unset},
    {"which", &my_which},
    {"where", &my_where},
    {"repeat", &my_repeat},
    {"fg", &my_fg},
    {"jobs", &my_jobs},
    {NULL, NULL}
};
