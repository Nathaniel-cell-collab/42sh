/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** parsing of ops
*/

#include "../../include/parser.h"
#include "../../include/my_strings.h"
#include "../../include/my_free.h"

static int isop(char *ptr)
{
    for (int i = 0; OP_TAB[i].op; i++) {
        if (!strncmp(ptr, OP_TAB[i].op, OP_TAB[i].len))
            return 1;
    }
    return 0;
}

int check_token(char *str)
{
    char *ptr = str;
    char *tok = NULL;

    if (ptr[0] == '(')
        return 0;
    tok = strchr(str, '(');
    if (!tok)
        return 0;
    if (tok[-1] == '$')
        return 0;
    while (ptr < tok) {
        if (isop(ptr))
            return 0;
        ptr++;
    }
    return 84;
}

int check_parenthese(char *str, char op)
{
    int count = 0;
    char temp = 0;

    if (check_token(str)) {
        dprintf(2, "Invalid token. \"(\"\n");
        return 84;
    }
    for (int i = 0; str[i]; i++) {
        if (str[i] == '(')
            count++;
        if (str[i] == ')')
            count--;
    }
    if (count < 0)
        temp = ')';
    if (0 < count)
        temp = op;
    if (count)
        dprintf(2, "Too many %c's.\n", temp);
    return count;
}

int check_double(char *str, char op)
{
    int count = 0;
    char res = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] == op)
            count++;
    if (count % 2 != 0) {
        res++;
        dprintf(2, "Unmatched '%c'.\n", op);
    }
    return res;
}

int check_line(char *line)
{
    for (int i = 0; OP_TAB[i].op; i++)
        if (OP_TAB[i].parse_func
            && OP_TAB[i].parse_func(line, OP_TAB[i].op[0]))
            return 84;
    return 0;
}
