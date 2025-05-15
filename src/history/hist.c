/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** history
*/
#include "history.h"

bool history_clear(void)
{
    int fd = 0;

    fd = open(HISTORY_FILE, O_CREAT | O_TRUNC);
    if (fd == -1)
        return false;
    return true;
}

bool append_to_history(int fd, history_t *history)
{
    if (!history)
        return false;
    if (history->cmd_line[0] == ' ' || history->cmd_line[0] == '\0')
        return true;
    append_to_history(fd, history->next);
    write(fd, history->cmd_line, strlen(history->cmd_line));
    if (history->cmd_line[strlen(history->cmd_line) - 1] != '\n')
        dprintf(fd, "\n");
    return true;
}

void history_to_file(history_t *history)
{
    int fd = open(HISTORY_FILE, O_TRUNC | O_WRONLY | O_CREAT, 00644);

    if (fd == -1)
        return;
    append_to_history(fd, history);
    close(fd);
}
