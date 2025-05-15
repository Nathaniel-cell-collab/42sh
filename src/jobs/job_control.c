/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** job_control
*/

#include "mysh.h"

void free_jobs(job_t *job)
{
    if (!job)
        return;
    free_jobs(job->next);
    free(job);
}

int is_process_running(pid_t pid)
{
    char *buffer = xcalloc(6 + nbrlen(pid) + 1, sizeof(char));

    sprintf(buffer, "/proc/%d", pid);
    if (!access(buffer, F_OK)) {
        my_free(&buffer);
        return 1;
    }
    my_free(&buffer);
    return 0;
}

void update_jobs(mysh_t *mysh)
{
    job_t *job = mysh->j;
    job_t *temp = NULL;

    if (!is_process_running(mysh->j->pgid) && mysh->j->id != 0) {
        temp = mysh->j;
        mysh->j = temp->next;
        free(temp);
        return;
    }
    while (mysh->j->next) {
        if (!is_process_running(mysh->j->next->pgid)
            && mysh->j->next->id != 0) {
            temp = mysh->j->next;
            mysh->j->next = temp->next;
            free(temp);
        }
        mysh->j = mysh->j->next;
    }
    mysh->j = job;
}

static void dump_jobs(job_t *job)
{
    job_t *j = NULL;

    for (j = job; j; j = j->next) {
        if (j->id == 0)
            continue;
        printf("[%d]    %d  running.\n", j->id, j->pgid);
    }
}

char **my_jobs(mysh_t *mysh, UNUSED char **command)
{
    dump_jobs(mysh->j);
    return mysh->env;
}

job_t *push_job(job_t **oldjob, pid_t pgid)
{
    job_t *new_job = xcalloc(1, sizeof(job_t));

    new_job->id = (*oldjob)->id + 1;
    new_job->pgid = pgid;
    new_job->stderr = STDERR_FILENO;
    new_job->stdin = STDIN_FILENO;
    new_job->stdout = STDOUT_FILENO;
    new_job->next = *oldjob;
    *oldjob = new_job;
    return new_job;
}
