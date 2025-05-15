/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** xcalloc
*/

#include "header.h"

void *xcalloc(size_t nmemb, size_t size)
{
    void *ptr = calloc(nmemb, size);

    if (!ptr) {
        perror("malloc");
        exit(84);
    }
    return ptr;
}
