/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** free_shell
*/

#include "mysh.h"
#include "history.h"

void free_shell(mysh_t *mysh)
{
    free_array_alias(mysh->alias);
    history_to_file(mysh->history);
    free_pile(mysh->history);
    free_jobs(mysh->j);
    my_free_array(mysh->env);
    my_free_array(mysh->local_env);
    my_free(&(mysh->line));
    my_free(&(mysh->clean_line));
    bt_free(mysh->root);
    my_free(&(mysh->nline));
    my_free(&mysh);
}
