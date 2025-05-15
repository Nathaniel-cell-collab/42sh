/*
** EPITECH PROJECT, 2025
** teksh
** File description:
** skip_space
*/

#include "my_strings.h"

char *skip_char(char *str, char *to_skip)
{
    int str_index = 0;
    int real_index = 0;
    bool is_in_quotes = false;

    for (str_index = 0; str[str_index]; str_index++) {
        if (str[str_index] == '\'')
            is_in_quotes = !is_in_quotes;
        if (is_in_quotes == true)
            continue;
        if (!is_instr(to_skip, str[str_index]))
            return str + real_index;
        real_index++;
    }
    return str + real_index;
}
