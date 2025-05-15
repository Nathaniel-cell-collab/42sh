/*
** EPITECH PROJECT, 2025
** my_isalpha
** File description:
** return 1 if a char is alphanumeric
*/

int my_is_alpha(char c)
{
    if (c >= 48 && c <= 57)
        return 1;
    if (c >= 97 && c <= 122)
        return 1;
    if (c >= 65 && c <= 90)
        return 1;
    return 0;
}

int my_str_is_alphanum_and(char *str, char c)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (my_is_alpha(str[i]) != 1 && str[i] != c)
            return 0;
    }
    return 1;
}
