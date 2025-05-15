/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** init_pile
*/
#include "history.h"

char *get_cmd_with_id(unsigned int id, history_t **stack)
{
    history_t *tmp = NULL;

    if (!stack)
        return NULL;
    tmp = *stack;
    while (tmp) {
        if (tmp->id == id)
            return xstrdup(tmp->cmd_line);
        tmp = tmp->next;
    }
    return NULL;
}

history_t *init_stack(char *cmd)
{
    history_t *history = NULL;

    if (!cmd)
        return NULL;
    history = xcalloc(1, sizeof(history_t));
    history->cmd_line = xstrdup(cmd);
    history->id = 1;
    history->next = NULL;
    return history;
}

history_t *add(history_t **stack, char *cmd)
{
    history_t *history = NULL;

    if (!cmd)
        return NULL;
    if (!stack)
        return init_stack(cmd);
    if (!(*stack))
        return init_stack(cmd);
    history = init_stack(cmd);
    history->id = (*stack)->id + 1;
    history->next = *stack;
    return history;
}

history_t *pop(history_t **stack)
{
    history_t *val = NULL;

    if (!stack)
        return NULL;
    val = *stack;
    *stack = (*stack)->next;
    val->next = NULL;
    return val;
}
