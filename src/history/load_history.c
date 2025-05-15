/*
** EPITECH PROJECT, 2025
** 42sh
** File description:
** loadhistory
*/
#include "history.h"
#include "my_free.h"

bool create_file(char *pathname)
{
    int fd = 0;

    if (!access(pathname, F_OK))
        return true;
    if (!pathname)
        return false;
    fd = open(pathname, O_CREAT, 0664);
    if (fd == -1) {
        perror("open");
        return false;
    }
    close(fd);
    return true;
}

history_t *load_history(void)
{
    history_t *history = NULL;
    char *lineptr = NULL;
    size_t n = 0;
    FILE *stream = NULL;

    if (!create_file(HISTORY_FILE))
        return NULL;
    stream = fopen(HISTORY_FILE, "r");
    if (!stream)
        return NULL;
    while (getline(&lineptr, &n, stream) != -1) {
        if (lineptr[strlen(lineptr) - 1] == '\n')
            lineptr[strlen(lineptr) - 1] = 0;
        history = add(&history, lineptr);
    }
    my_free(&lineptr);
    fclose(stream);
    return history;
}
