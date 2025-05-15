/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** init_job
*/

#include "mysh.h"

job_t *init_job(mysh_t *mysh)
{
    job_t *first_job = xcalloc(1, sizeof(job_t));

    first_job->id = 0;
    first_job->pgid = mysh->shell_pgid;
    first_job->stderr = STDERR_FILENO;
    first_job->stdin = STDIN_FILENO;
    first_job->stdout = STDOUT_FILENO;
    first_job->next = NULL;
    return first_job;
}
