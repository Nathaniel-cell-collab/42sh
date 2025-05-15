/*
** EPITECH PROJECT, 2024
** minishell
** File description:
** word_array
*/

#include <stdio.h>
#include "mysh.h"

int count_words(const char *str, char *separators)
{
    int i = 0;
    int compteur = 0;
    bool in_word = false;
    bool in_quote = false;

    while (str[i] != '\0') {
        if (str[i] == '\'')
            in_quote = !in_quote;
        if ((!is_instr(separators, str[i]) || in_quote) && !in_word) {
            compteur++;
            in_word = true;
        } else {
            in_word = false;
        }
        i++;
    }
    return compteur;
}

int count_separators(char *str, int len_tot, int d)
{
    int compteur = 0;

    while (str[compteur] == '\0' && compteur + d < len_tot)
        compteur = compteur + 1;
    return compteur;
}

char *transform(char const *str, char *separators)
{
    int i = 0;
    char *strm = NULL;
    bool is_in_quotes = false;

    strm = xcalloc((strlen(str) + 1), sizeof(char));
    if (!strm)
        return NULL;
    while (str[i] != 0) {
        if (str[i] == '\'')
            is_in_quotes = !is_in_quotes;
        if (is_instr(separators, str[i]) && !is_in_quotes)
            strm[i] = '\0';
        else
            strm[i] = str[i];
        i = i + 1;
    }
    strm[i] = '\0';
    return strm;
}

char **word_array(char const *str, char separa[])
{
    char *strm = transform(str, separa);
    int len_tot = strlen(str);
    char **array = xcalloc((count_words(str, separa) + 1), sizeof(char *));
    int d = 0;
    int i = 0;
    int separators = count_separators(strm, len_tot, d);

    while (d < len_tot - separators) {
        array[i] = xstrdup(strm + d + separators);
        d += strlen(array[i]);
        separators = separators + count_separators(strm + d + separators,
        len_tot, d + separators);
        i = i + 1;
    }
    free(strm);
    array[i] = NULL;
    return array;
}
