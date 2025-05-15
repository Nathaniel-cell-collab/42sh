/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** replace_var
*/

#include "mysh.h"

static size_t llen_var(char *line)
{
    size_t i = 1;

    while (isalnum(line[i])) {
        i++;
    }
    return i;
}

char **lget_all_value(char **array, char **env)
{
    char **value_array = xcalloc(1, sizeof(char *));
    char *value = NULL;
    int j = 0;

    for (int i = 0; array[i]; i++) {
        value = my_get_env(env, array[i]);
        if (!value)
            continue;
        value = xstrdup(value + 1);
        value_array = reallocarray(value_array, j + 2, sizeof(char *));
        if (!value_array)
            exit(84);
        value_array[j] = value;
        j++;
    }
    value_array[j] = NULL;
    return value_array;
}

char **lget_all_var(char *line, char **env)
{
    char **var_array = xcalloc(1, sizeof(char *));
    int j = 0;
    char *var = NULL;

    for (int i = 0; line[i]; i++) {
        if (line[i] != '$')
            continue;
        var = my_strndup(line, i + 1, llen_var(line + i));
        if (!my_get_env(env, var)) {
            my_free(&var);
            continue;
        }
        var_array = reallocarray(var_array, j + 2, sizeof(char *));
        if (!var_array)
            exit(84);
        var_array[j] = var;
        j++;
    }
    var_array[j] = NULL;
    return var_array;
}

static size_t get_tot_size(char **arr1, char **arr2)
{
    int len1 = 0;
    size_t size1 = 0;
    int len2 = 0;
    size_t size2 = 0;

    get_arr_info(arr2, &len2, &size2);
    get_arr_info(arr1, &len1, &size1);
    return size2 - (size1 + len1);
}

static bool check_loc_var(char *line)
{
    return line[0] == '$';
}

char *lhget_full_cmd(mysh_t *mysh, char **array, bool (*cfunc)(char *),
    size_t (*size_func)(char *))
{
    int j = 0;
    int i = 0;
    int len = 0;
    char *new_line = xcalloc(mysh->csize + strlen(mysh->nline) + 2,
    sizeof(char));

    while (mysh->nline[i]) {
        if (cfunc(mysh->nline + i) && array[len]) {
            new_line = strcat(new_line, array[len]);
            j += strlen(array[len]);
            len++;
            i += size_func(mysh->nline + i) + 1;
        }
        new_line[j] = mysh->nline[i];
        i += mysh->nline[i] ? 1 : 0;
        j++;
    }
    return new_line;
}

void lget_cmd(mysh_t *mysh)
{
    char **var_array = NULL;
    char **value_array = NULL;
    char *new_line = NULL;

    mysh->csize = 0;
    var_array = lget_all_var(mysh->nline, mysh->local_env);
    value_array = lget_all_value(var_array, mysh->local_env);
    if (!value_array[0]) {
        my_free_array(var_array);
        my_free_array(value_array);
        return;
    }
    mysh->csize = get_tot_size(var_array, value_array);
    my_free_array(var_array);
    new_line = lhget_full_cmd(mysh, value_array, &check_loc_var, &llen_var);
    my_free(&(mysh->nline));
    mysh->nline = new_line;
    my_free_array(value_array);
}
