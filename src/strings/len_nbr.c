/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** len_nbr
*/

int nbrlen(int n)
{
    int len = 0;

    if (n == 0)
        return 1;
    if (n < 0) {
        n = -n;
    }
    while (n > 0) {
        n /= 10;
        len++;
    }
    return len;
}
