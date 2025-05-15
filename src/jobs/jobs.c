/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** jobs
*/

#include "mysh.h"

void restore_sig(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    signal(SIGTSTP, SIG_DFL);
    signal(SIGTTIN, SIG_DFL);
    signal(SIGTTOU, SIG_DFL);
    signal(SIGCHLD, SIG_DFL);
}

void launch_process(mysh_t *mysh, ast_t *root, pid_t pgid)
{
    pid_t pid = 0;

    if (mysh->shell_is_interactive) {
        pid = getpid();
        if (pgid != pid)
            pgid = pid;
        setpgid(pid, pgid);
        restore_sig();
    }
    exec_sh(mysh, root->cmd);
    exit(1);
}

void bring_to_foreground(job_t *job, mysh_t *mysh)
{
    int status = 0;

    tcsetpgrp(mysh->shell_terminal, job->pgid);
    kill(-(job->pgid), SIGCONT);
    waitpid(-(job->pgid), &status, WUNTRACED);
    tcsetpgrp(mysh->shell_terminal, mysh->shell_pgid);
    tcsetattr(mysh->shell_terminal, TCSADRAIN, &(mysh->shell_tmodes));
}

char **my_fg(mysh_t *mysh, char **command)
{
    int id = 0;
    job_t *j = NULL;

    if (mysh->j->id == 0) {
        dprintf(2, "No such jobs is running.\n");
        return mysh->env;
    }
    if (!command[1])
        bring_to_foreground(mysh->j, mysh);
    id = atoi(command[1]);
    if (id == 0)
        return mysh->env;
    for (j = mysh->j; j; j = j->next) {
        if (j->id == id) {
            bring_to_foreground(j, mysh);
            return mysh->env;
    }
    }
    dprintf(2, "fg: No such job: %s\n", command[1]);
    return mysh->env;
}

int jobs_control(ast_t *root, mysh_t *mysh)
{
    pid_t pid = 0;

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(84);
    }
    if (pid == 0) {
        launch_process(mysh, root->left, mysh->shell_pgid);
    }
    mysh->j = push_job(&(mysh->j), pid);
    printf("[%d] %d\n", mysh->j->id, pid);
    return bt_exec(root->right, mysh);
}
