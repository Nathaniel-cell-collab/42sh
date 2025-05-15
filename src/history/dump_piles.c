/*
** EPITECH PROJECT, 2025
** mysh
** File description:
** dump_pile
*/
#include "history.h"
#include "mysh.h"

void dump_stack(history_t *history)
{
    history_t *tmp = NULL;

    if (!history)
        return;
    tmp = history;
    while (tmp) {
        printf("%d %s", tmp->id, tmp->cmd_line);
        if (tmp->cmd_line[strlen(tmp->cmd_line) - 1] != '\n')
            printf("\n");
        tmp = tmp->next;
    }
    return;
}

void print_history_line(history_t *history)
{
    if (!history)
        return;
    print_history_line(history->next);
    printf("%d %s", history->id, history->cmd_line);
    if (history->cmd_line[strlen(history->cmd_line) - 1] != '\n')
        printf("\n");
}

char **dump_history(mysh_t *mysh, char **command)
{
    if (command[1] && !strcmp(command[1], "-c")) {
        history_clear();
        free_pile(mysh->history);
        mysh->history = NULL;
        return mysh->env;
    }
    print_history_line(mysh->history);
    return mysh->env;
}
