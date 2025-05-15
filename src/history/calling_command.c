/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** calling_command
*/

#include <ctype.h>
#include "history.h"
#include "my_strings.h"
#include "mysh.h"

size_t hcount_len_id(char *line)
{
    size_t i = 1;

    while (isdigit(line[i]))
        i++;
    return i;
}

char **hget_all_cmd(char *line, mysh_t *mysh, size_t *size)
{
    char **cmd_array = xcalloc(1, sizeof(char *));
    int j = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] != '!' || !isdigit(line[i + 1]))
            continue;
        *size += hcount_len_id(line + i);
        cmd_array = realloc(cmd_array, (j + 2) * sizeof(char *));
        if (!cmd_array)
            exit(84);
        cmd_array[j] = get_cmd_with_id(atoi(line + i + 1), &(mysh->history));
        if (!cmd_array[j]) {
            my_free_array(cmd_array);
            return NULL;
        }
        j++;
    }
    cmd_array[j] = NULL;
    return cmd_array;
}

void hget_full_cmd(char *dest, char *line, char **cmd_array)
{
    int j = 0;
    int i = 0;
    int len = 0;

    while (line && line[i]) {
        if (line[i] == '!' && isdigit(line[i + 1])) {
            dest = strcat(dest, cmd_array[len]);
            j += strlen(cmd_array[len]);
            len++;
            i += hcount_len_id(line + i);
        }
        dest[j] = line[i];
        j++;
        i++;
    }
}

void hget_cmd(mysh_t *mysh)
{
    int len = 0;
    size_t size_arr = 0;
    size_t id_size = 0;
    char *new_cmd = NULL;
    char **cmd_array = hget_all_cmd(mysh->nline, mysh, &id_size);

    if (!cmd_array) {
        dprintf(2, "Bad events uses.\n");
        return;
    }
    get_arr_info(cmd_array, &len, &size_arr);
    new_cmd = xcalloc(size_arr + (strlen(mysh->nline) - id_size) + 1,
    sizeof(char));
    hget_full_cmd(new_cmd, mysh->nline, cmd_array);
    my_free(&(mysh->nline));
    mysh->nline = new_cmd;
    my_free_array(cmd_array);
}
