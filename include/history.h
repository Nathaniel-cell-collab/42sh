/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** point_h
*/

#ifndef HISTORY_H_
    #define HISTORY_H_
    #include <string.h>
    #include <stdbool.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #define HISTORY_FILE ".history"
    #include "struct_mysh.h"
    #include "my_free.h"

    /*history*/
bool append_to_history(int fd, history_t *history);
bool history_clear(void);
history_t *load_history(void);
char **dump_history(mysh_t *mysh, char **command);

    /*pile*/
void hget_cmd(mysh_t *mysh);
char *call_command(char *ptr, history_t *history);
char *get_cmd_with_id(unsigned int id, history_t **stack);
history_t *init_stack(char *cmd);
history_t *add(history_t **stack, char *cmd);
history_t *pop(history_t **stack);
void free_pile(history_t *history);
void dump_stack(history_t *history);
void history_to_file(history_t *history);
#endif
