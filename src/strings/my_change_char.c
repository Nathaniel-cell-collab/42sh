/*
** EPITECH PROJECT, 2025
** my_tab_to_space
** File description:
** change a character of a string in another character
*/

#include "my_strings.h"

char *my_str_change_char(char *str, char *to_change, char for_change)
{
    bool is_in_quotes = false;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\'')
            is_in_quotes = !is_in_quotes;
        if (is_in_quotes == true)
            continue;
        if (is_instr(to_change, str[i]))
            str[i] = for_change;
    }
    if (is_in_quotes == true)
        return NULL;
    return str;
}
