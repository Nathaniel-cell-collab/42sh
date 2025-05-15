/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** my_strings
*/

#ifndef MY_STRINGS_H_
    #define MY_STRINGS_H_
    #include "header.h"

void get_arr_info(char **arr, int *len, size_t *size);
char *without_quotes(char *str);
char *my_str_change_char(char *str, char *to_change, char for_change);
int is_instr(char *str, char c);
int my_len_array(char **array);
void print_tab(char **tab);
int my_str_is_alphanum_and(char *str, char c);
char *skip_char(char *str, char *to_skip);
char *clean_str(char *str);
char *my_strndup(char const *src, int start, int end);
char *get_full_path(char *dir, char *exec);
char **word_array(char const *str, char separa[]);
char **my_push_tab(char **src, char *to_push);
char *array_to_str(char **array);
int nbrlen(int n);
#endif /* !MY_STRINGS_H_ */
