/*
** EPITECH PROJECT, 2025
** B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet
** File description:
** struct_mysh
*/

#ifndef STRUCT_MYSH_H_
    #define STRUCT_MYSH_H_
    #include "header.h"
//#include "history.h"
    #include "myrc.h"

//parsing struct
typedef enum node_type_s {
    CMD,
    SEMICOLON,
    S_REDIRECT_OUT,
    S_REDIRECT_IN,
    D_REDIRECT_OUT,
    D_REEDIRECT_IN,
    PIPE,
    AND,
    OR,
    BACK_TIC,
    D_QUOTE,
    S_QUOTE,
    S_PARENTHESE,
    E_PARENTHESE,
    JOBS
} node_type_t;

typedef struct ast_s {
    node_type_t type;
    struct ast_s *left;
    struct ast_s *right;
    char *cmd;
} ast_t;

typedef struct op_s {
    char *op;
    int priority;
    int len;
    node_type_t type;
    int (*func)();
    int (*parse_func)(char *, char);
    bool mode;
} op_t;

extern const op_t OP_TAB[];

//project struct
typedef struct builtin_s {
    char *name;
    char **(*func)();
} builtin_t;

typedef struct history_s {
    unsigned int id;
    char *cmd_line;
    struct history_s *next;
} history_t;

/* A job is a pipeline of processes.  */
typedef struct job {
    struct job *next;           /* next active job */
    pid_t pgid;                 /* process group ID */
    char notified;              /* true if user told about stopped job */
    struct termios tmodes;      /* saved terminal modes */
    int stdin;
    int stdout;
    int stderr;
    int id;  /* standard i/o channels */
} job_t;

typedef struct mysh_s {
    alias_t **alias;
    ast_t *root;
    char **env;
    char **local_env;
    char *line;
    char *clean_line;
    char *nline;
    int status;
    int priority;
    history_t *history;
    size_t csize;
    pid_t *pids;
    pid_t shell_pgid;
    job_t *j;
    struct termios shell_tmodes;
    int shell_terminal;
    int shell_is_interactive;
} mysh_t;

extern const struct builtin_s BUILTIN_FUNCS[];
#endif /* !STRUCT_MYSH_H_ */
