/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** loop
*/

#include "mysh.h"

void push_sate(mysh_t *mysh)
{
    char buf[4] = {0};

    sprintf(buf, "%d", mysh->status);
    my_set(mysh, (char *[]){"set", "?", buf, NULL});
}

int loop(mysh_t *mysh)
{
    update_jobs(mysh);
    if (check_line(mysh->line))
        return 84;
    mysh->clean_line = clean_str(mysh->line);
    if (mysh->clean_line[0] == '@') {
        dprintf(2, "@: Bad token use.\n");
        mysh->status = 84;
        return 84;
    }
    if (verif_alias(mysh, mysh->clean_line, mysh->alias) ||
            verif_unalias(mysh, mysh->clean_line))
        return 0;
    mysh->history = add(&(mysh->history), format_line(mysh, mysh->clean_line));
    mysh->root = create_ast(mysh->clean_line, mysh->root);
    mysh->status = bt_exec(mysh->root, mysh);
    return 0;
}
