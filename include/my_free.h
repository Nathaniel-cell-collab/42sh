/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** my_free
*/

#ifndef MY_FREE_H_
    #define MY_FREE_H_
    #include "header.h"

void my_free_array(char **array);
void my_free(void *ptr);
void *xcalloc(size_t nmemb, size_t size);
char *xstrdup(const char *str);
#endif /* !MY_FREE_H_ */
