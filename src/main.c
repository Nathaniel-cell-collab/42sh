/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** main
*/

#include "../include/mysh.h"
#include <readline/readline.h>
#include <readline/history.h>


void get_prompt(char **env, char buffer[8192])
{
    char cwd[PATH_MAX] = {0};
    char hostname[HOST_NAME_MAX] = {0};
    char symbol = (geteuid() == 0) ? '#' : '$';
    const char *user = my_get_env(env, "USER");

    if (getcwd(cwd, sizeof(cwd)) == NULL)
        return;
    if (gethostname(hostname, sizeof(hostname)) != 0)
        return;
    sprintf(buffer, CYAN "%s" RESET "@"HOST "%s" RESET ":"PATH "%s" SYMBOL "%c>" RESET, user ? user + 1 : "unknown", hostname, cwd, symbol);
}

int main(UNUSED int ac, UNUSED char **av, char **env)
{
    mysh_t *mysh = init_shell(env);
    char prompt[8192] = {0};

    get_prompt(env, prompt);
    mysh->line = readline(prompt);
    while (mysh->line) {
        loop(mysh);
        add_history(mysh->line);
        my_free(&(mysh->line));
        my_free(&(mysh->clean_line));
        bt_free(mysh->root);
        mysh->root = NULL;
        mysh->line = readline(prompt);
    }
    free_shell(mysh);
    return 0;
}
