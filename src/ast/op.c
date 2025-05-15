/*
** EPITECH PROJECT, 2025
** teksh
** File description:
** op
*/

#include "../../include/mysh.h"

const op_t OP_TAB[] = {
    {"<<", 3, 2, D_REEDIRECT_IN, &d_redirect_in, NULL, true},
    {">>", 3, 2, D_REDIRECT_OUT, &redirect_out_func, NULL, true},
    {"<", 3, 1, S_REDIRECT_IN, &redirect_in_func, NULL, true},
    {">", 3, 1, S_REDIRECT_OUT, &redirect_out_func, NULL, true},
    {";", 5, 1, SEMICOLON, &semicolon_func, NULL, true},
    {"||", 4, 2, OR, &ast_or, NULL, true},
    {"|", 2, 1, PIPE, &pipe_func, NULL, true},
    {"&&", 4, 2, AND, &ast_and, NULL, true},
    {"@", 5, 1, JOBS, &jobs_control, NULL, true},
    {"\'", 1, 1, S_QUOTE, NULL, &check_double, false},
    {"\"", 1, 1, D_QUOTE, NULL, &check_double, false},
    {"`", 1, 1, BACK_TIC, NULL, &check_double, false},
    {"(", 1, 1, S_PARENTHESE, &ast_subshell, &check_parenthese, true},
    {0}
};
