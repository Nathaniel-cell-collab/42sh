/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** point_h
*/

#ifndef RC_H_
    #define RC_H_
    #include <string.h>
    #include <stdbool.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    #define RC_FILE ".myrc"

    /*structure*/
typedef struct alias_s {
    char *old_cmd;
    char *new_cmd;
} alias_t;

    /*myrc*/
char *get_usr_clean(alias_t **alias, char *user_alias);
alias_t **unalias(char *line, alias_t **alias);
int count_alias(alias_t **alias);
alias_t **aadd(char *line, alias_t **alias);
alias_t **init_array_alias(char *line, alias_t **alias);
bool is_alias(char *line);
void dump_alias(alias_t **alias);
alias_t *init_alias(char *new, char *old);
void free_alias(alias_t *alias);
void free_array_alias(alias_t **alias);
void add_alias(char *old, char *new);
alias_t **load_alias(void);
#endif
