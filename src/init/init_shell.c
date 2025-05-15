/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** init_shell
*/

#include "history.h"
#include "mysh.h"

void default_sig(void)
{
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    signal(SIGTTOU, SIG_IGN);
    signal(SIGCHLD, SIG_IGN);
}

mysh_t *init_term(mysh_t *mysh)
{
    mysh->shell_terminal = STDIN_FILENO;
    mysh->shell_is_interactive = isatty(mysh->shell_terminal);
    mysh->shell_pgid = getpgrp();
    if (mysh->shell_is_interactive) {
        while (tcgetpgrp(mysh->shell_terminal) != mysh->shell_pgid) {
            kill(-mysh->shell_pgid, SIGTTIN);
            mysh->shell_pgid = getpgrp();
    }
    default_sig();
    mysh->shell_pgid = getpid();
    if (setpgid(mysh->shell_pgid, mysh->shell_pgid) < 0)
        exit(1);
    tcsetpgrp(mysh->shell_terminal, mysh->shell_pgid);
    tcgetattr(mysh->shell_terminal, &(mysh->shell_tmodes));
    }
    return mysh;
}

mysh_t *init_shell(char **env)
{
    mysh_t *mysh = xcalloc(1, sizeof(mysh_t));

    if (!mysh) {
        perror("calloc");
        exit(84);
    }
    mysh = init_term(mysh);
    mysh->j = init_job(mysh);
    mysh->alias = load_alias();
    mysh->history = load_history();
    mysh->clean_line = NULL;
    mysh->line = NULL;
    mysh->env = init_env(env);
    mysh->local_env = init_loc();
    return mysh;
}
