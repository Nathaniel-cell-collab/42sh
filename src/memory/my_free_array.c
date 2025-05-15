/*
** EPITECH PROJECT, 2025
** my_free_array
** File description:
** frre all the element of an array
*/

#include "my_free.h"

void my_free_array(char **array)
{
    int i = 0;

    if (!array)
        return;
    while (array[i] != NULL) {
        my_free(&array[i]);
        array[i] = NULL;
        i++;
    }
    free(array);
}
