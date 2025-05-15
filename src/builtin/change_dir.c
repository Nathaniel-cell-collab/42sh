/*
** EPITECH PROJECT, 2025
** change_dir
** File description:
** recreate cd builtin
*/

#include <stdlib.h>
#include <unistd.h>
#include "mysh.h"

int cd_home(char *pathname, char **pwd, char *currpath, mysh_t *mysh)
{
    char *home_path = NULL;

    if (!pathname || pathname[0] == '~') {
        home_path = my_get_env(mysh->env, "HOME=");
        if (!home_path)
            home_path = "/home";
        if (pathname && strlen(pathname) > 1) {
            pathname = get_full_path(home_path, pathname + 1);
        } else {
            pathname = home_path;
        }
        if (access(pathname, F_OK) == 0) {
            chdir(pathname);
            change_env(mysh, pathname, currpath, pwd);
            free(currpath);
            return 0;
        }
    }
    return -1;
}

int cd_minus(char *pathname, char **pwd, char *currpath, mysh_t *mysh)
{
    if (!pathname)
        return -1;
    if (strcmp(pathname, "-") == 0) {
        pathname = my_get_env(mysh->env, "OLDPWD=");
        if (!pathname)
            pathname = "/home";
        change_env(mysh, pathname, currpath, pwd);
        pathname = my_get_env(mysh->env, "PWD=");
        if (!pathname)
            return -1;
        chdir(pathname);
        free(currpath);
        return 0;
    }
    return -1;
}

void norm_cd(char *pathname, mysh_t *mysh, char *currpath, char **pwd)
{
    char *path = NULL;

    if (access(pathname, F_OK) == 0) {
        if (chdir(pathname) == -1)
            dprintf(2, "%s: Not a directory.\n", pathname);
        path = getcwd(path, 2048);
        change_env(mysh, path, currpath, pwd);
        free(path);
        free(currpath);
    } else {
        dprintf(2, "%s: No such file or directory.\n", pathname);
    }
}

char **change_dir(mysh_t *mysh, char **command)
{
    char **pwd = NULL;
    char *currpath = NULL;
    char *pathname = command[1];

    currpath = getcwd(currpath, 2048);
    if (cd_home(pathname, pwd, currpath, mysh) == 0)
        return mysh->env;
    if (cd_minus(pathname, pwd, currpath, mysh) == 0)
        return mysh->env;
    norm_cd(pathname, mysh, currpath, pwd);
    return mysh->env;
}
