/*
** EPITECH PROJECT, 2024
** is_instr
** File description:
** check if a char is in a string
*/

int is_instr(char *str, char c)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (c == str[i])
            return 1;
    }
    return 0;
}
