/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** free_pile
*/

#include "history.h"

void free_pile(history_t *history)
{
    if (!history)
        return;
    free_pile(history->next);
    if (history->cmd_line)
        free(history->cmd_line);
    free(history);
}
