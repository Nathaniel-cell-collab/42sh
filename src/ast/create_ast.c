/*
** EPITECH PROJECT, 2025
** teksh
** File description:
** create_ast
*/

#include "../../include/my_strings.h"
#include "../../include/parser.h"
#include "my_free.h"

static int parse_par(char *line)
{
    int i = 1;
    int count = 1;

    while (count > 0) {
        if (line[i] == ')')
            count--;
        if (line[i] == '(')
            count++;
        i++;
    }
    return i;
}

int search_op(char *ptr, int priority, ast_t *root)
{
    static bool ifpar = false;

    for (int i = 0; OP_TAB[i].op; i++) {
        if (ptr[0] == '(')
            ifpar = true;
        if (ptr[0] == ')')
            ifpar = false;
        if (ptr[0] == '(' && priority == 1) {
            root->type = S_PARENTHESE;
            ifpar = false;
            return parse_par(ptr);
        }
        if (!strncmp(OP_TAB[i].op, ptr, OP_TAB[i].len) &&
            OP_TAB[i].priority == priority && OP_TAB[i].mode == true
            && ifpar == false) {
            root->type = OP_TAB[i].type;
            return OP_TAB[i].len;
        }
    }
    return 0;
}

ast_t *init_node(void)
{
    ast_t *node = xcalloc(1, sizeof(ast_t));

    node->left = NULL;
    node->cmd = NULL;
    node->right = NULL;
    node->type = CMD;
    return node;
}

void error_message(node_type_t type)
{
    if (type == SEMICOLON)
        return;
    if (type == PIPE) {
        dprintf(2, PIPE_ERR_MESSAGE);
    } else {
        dprintf(2, REDRIRECT_ERR_MESSAGE);
    }
}

static int create_branche(ast_t *root, char *line, int i, int jump)
{
    ast_t *left = init_node();
    ast_t *right = init_node();

    if (!left || !right)
        return -1;
    if (root->type == S_PARENTHESE) {
        left->cmd = my_strndup(line, i + 1, jump - 2);
        root->left = left;
        root->right = NULL;
        free_node(right);
        return 0;
    }
    left->cmd = my_strndup(line, 0, i);
    right->cmd = my_strndup(line, i + jump, strlen(line) - (i + 1));
    root->left = create_ast(left->cmd, left);
    root->right = create_ast(right->cmd, right);
    return 0;
}

static bool verif_line(char *vline, ast_t *root)
{
    char *op_verif = "|><;";

    return (vline[0] == 0 && root->type != SEMICOLON
        && root->type != S_PARENTHESE && root->type != JOBS)
        || (is_instr(op_verif, vline[0]) && root->type != S_PARENTHESE &&
        root->type != JOBS);
}

ast_t *browse_line(char *line, int priority, ast_t *root, int *count)
{
    int jump = 0;
    char *vline = NULL;

    for (int i = 0; line[i]; i++) {
        jump = search_op(line + i, priority, root);
        if (!jump)
            continue;
        vline = skip_char(line + i + jump, " \t");
        if (verif_line(vline, root)) {
            error_message(root->type);
            return NULL;
        }
        create_branche(root, line, i, jump);
        if (!(root->left) && !(root->right))
            return NULL;
        return root;
    }
    *count = -1;
    return root;
}

ast_t *create_ast(char *line, ast_t *root)
{
    int priority = MAX_PRIORITY;
    int count = 0;

    if (!root) {
        root = init_node();
        root->cmd = xstrdup(line);
    }
    if (!root || !(root->cmd))
        return NULL;
    while (priority > 0) {
        count = 0;
        root = browse_line(line, priority, root, &count);
        if (!root)
            return NULL;
        if (count == 0)
            break;
        priority--;
    }
    return root;
}
