/*
** EPITECH PROJECT, 2025
** AST
** File description:
** my
*/

#ifndef PARSER_H_
    #define PARSER_H_
    #include "header.h"
    #include "struct_mysh.h"
    #include <glob.h>
    #define MAX_PRIORITY 5
    #define REDRIRECT_ERR_MESSAGE "Missing name for redirect.\n"
    #define PIPE_ERR_MESSAGE "Invalid null command.\n"

//check args before ast
int check_line(char *line);
int check_double(char *str, char op);
int check_parenthese(char *str, char op);

//create ast
char *search_file(char *ptr);
void bt_free(ast_t *root);
void restore_fd(int save_stdin, int save_stdout);
void bt_pprint(ast_t *root);
void free_node(ast_t *node);
ast_t *create_ast(char *line, ast_t *root);
int handle_globbings(mysh_t *mysh);
int handle_back(mysh_t *mysh);
#endif /* !PARSER_H_ */
