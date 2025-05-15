/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** mysh
*/

#ifndef MYSH_H_
    #define MYSH_H_
    #include "header.h"
    #include "struct_mysh.h"
    #include "parser.h"
    #include "my_strings.h"
    #include "my_free.h"
    #include "history.h"
    #include <limits.h>
    #include <pwd.h>
    #define CYAN "\033[1;36m"
    #define HOST "\033[1;35m"
    #define PATH "\033[1;34m"
    #define SYMBOL "\033[1;33m"
    #define RESET "\033[0m"
    #define EXEC_FORMAT "%s: Exec format error. Binary file not executable.\n"
    #define BAD_CMD "%s: Command not found.\n"
    #define BAD_PERM "%s: Permission denied.\n"
    #define UNUSED __attribute__((unused))

//ast function:
int jobs_control(ast_t *root, mysh_t *mysh);
int ast_and(ast_t *root, mysh_t *mysh);
int bt_exec(ast_t *root, mysh_t *mysh);
int call_ast(pid_t pid1, ast_t *right, mysh_t *mysh);
int d_redirect_in(ast_t *root, mysh_t *mysh);
int redirect_in_func(ast_t *root, mysh_t *mysh);
int redirect_out_func(ast_t *root, mysh_t *mysh);
int pipe_func(ast_t *root, mysh_t *mysh);
int semicolon_func(ast_t *root, mysh_t *mysh);
int ast_or(ast_t *root, mysh_t *mysh);
int ast_subshell(ast_t *root, mysh_t *mysh);
//shell function:
char *format_line(mysh_t *mysh, char *line);
char **my_jobs(mysh_t *mysh, UNUSED char **command);
void free_jobs(job_t *job);
void update_jobs(mysh_t *mysh);
int is_process_running(pid_t pid);
void restore_sig(void);
char **my_fg(mysh_t *mysh, char **command);
job_t *init_job(mysh_t *mysh);
job_t *push_job(job_t **oldjob, pid_t pgid);
char *get_under_back(char *line, int *size);
char *bget_new_cmd(char *cmd, int size, char *output);
char *format_line(mysh_t *mysh, char *line);
void push_sate(mysh_t *mysh);
int loop(mysh_t *mysh);
void lget_cmd(mysh_t *mysh);
char **my_unset(mysh_t *mysh, char **command);
char **my_unset_var(char **old_env, char **command);
char **my_set(mysh_t *mysh, char **command);
char **init_loc(void);
char **my_set_var(char **old_env, char **command, char *name);
void get_error(int err, char *command);
char **dump_history(mysh_t *mysh, char **command);
mysh_t *init_shell(char **env);
char *my_get_env(char **env, char *var_env);
char **cpy_env_and_add(char **env, int resize, char *element);
char **my_setenv(mysh_t *mysh, char **command);
char **my_unsetenv(mysh_t *mysh, char **command);
char **init_env(char **env);
void free_shell(mysh_t *mysh);
int get_command_line(mysh_t *mysh);
char **change_dir(mysh_t *mysh, char **command);
char **print_env(mysh_t *mysh);
bool is_bt(char *command);
char *try_full_path(char *dir, char *full_path, char **command);
char **my_which(mysh_t *mysh, char **command);
char **my_where(mysh_t *mysh, char **command);
void change_env(mysh_t *mysh, char *pathname, char *currpath, char **pwd);
int exec_sh(mysh_t *mysh, char *line);
char *find_full_path(char **command, char **env);
char **my_builtin(char **command, mysh_t *mysh, int *exec);
int handle_alias(mysh_t *mysh);
char **my_repeat(mysh_t *mysh, char **command);
int verif_unalias(mysh_t *mysh, char *line);
int verif_alias(mysh_t *mysh, char *line, alias_t **alias);
#endif /* !MYSH_H_ */
