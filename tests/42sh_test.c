/*
** EPITECH PROJECT, 2024
** my_printf test
** File description:
** Test
*/
#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/history.h"
#include "../include/my_strings.h"
#include "../include/mysh.h"
#include "../include/parser.h"
#include "../include/my_free.h"

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

char *env[] = { "SHELL=/bin/bash", "USER=samuel", 
    "PWD=/home/samuel/delivery/B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet",
    "HOME=/home/samuel", "USERNAME=samuel", 
    "PATH=/home/samuel/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin",
    "OLDPWD=/home/samuel/delivery/B-PSU-200-RUN-2-1-42sh-quentin-stephane.taranne-payet/src/memory",
    NULL
};

Test(quarantedeuxsh, history, .init = redirect_all_std)
{
    history_t *history = load_history();

    history_to_file(history);
}

Test(quarantedeuxsh, history_clear, .init = redirect_all_std)
{
    cr_assert(history_clear() == true);
}

Test(ast, semicolon, .init = redirect_all_std)
{
    ast_t *root = NULL;
    char *line = strdup("ls; ls | cat -e > blue\n");

    root = create_ast(line, root);
    mysh_t *mysh = init_shell(env);

    cr_assert(semicolon_func(root, mysh) == 0);
}

Test(quarantedeuxsh, pile_init, .init = redirect_all_std)
{
    history_t *history = init_stack("toto");

    cr_assert_str_eq("toto", history->cmd_line);
    cr_assert_null(init_stack(NULL), "not NULL !");
    free_pile(history);

}

Test(quarantedeuxsh, pile_add, .init = redirect_all_std)
{
    history_t *history = init_stack("toto");
    history_t *nil = NULL;

    history = add(&history, "deuxieme");
    history = add(&history, "troisieme");
    history = add(&history, "quatrieme");
    history = add(&history, "cinquieme");
    nil = add(&history, NULL);
    nil = add(NULL, NULL);
    nil = add(NULL, "nul");
    cr_assert_str_eq("cinquieme", history->cmd_line);
    cr_assert_str_eq("quatrieme", history->next->cmd_line);
    cr_assert_str_eq("nul", nil->cmd_line);
    free_pile(history);
    free_pile(nil);
}

Test(quarantedeuxsh, pile_pop, .init = redirect_all_std)
{
    history_t *history = init_stack("toto");
    history_t *value = NULL;
    history_t *nil = NULL;
    history_t *value2 = NULL;

    history = add(&history, "deuxieme");
    history = add(&history, "troisieme");
    history = add(&history, "quatrieme");
    history = add(&history, "cinquieme");
    value = pop(&history);
    nil = pop(NULL);
    cr_assert_str_eq("cinquieme", value->cmd_line);
    cr_assert_str_eq("quatrieme", history->cmd_line);
    value2 = pop(&history);
    cr_assert_str_eq("quatrieme", value2->cmd_line);
    cr_assert_str_eq("troisieme", history->cmd_line);
    dump_stack(NULL);
    dump_stack(history);
    free_pile(history);
    free_pile(nil);
    free_pile(value);
    free_pile(value2);
}

Test(quarantedeuxsh, pile_get_id, .init = redirect_all_std)
{
    history_t *history = init_stack("toto");
    history_t *value = NULL;
    history_t *nil = NULL;
    history_t *value2 = NULL;
    char *val1 = NULL;
    char *val2 = NULL;
    char *val3 = NULL;

    history = add(&history, "deuxieme");
    history = add(&history, "troisieme");
    history = add(&history, "quatrieme");
    history = add(&history, "cinquieme");
    value = pop(&history);
    nil = pop(NULL);
    value2 = pop(&history);
    val1 = get_cmd_with_id(1, &history);
    val2 = get_cmd_with_id(2, &history);
    val3 = get_cmd_with_id(3, &history);
    cr_assert_null(get_cmd_with_id(-1, NULL), "not null");
    cr_assert_null(get_cmd_with_id(-1, &history), "not NULL !");
    cr_assert_null(get_cmd_with_id(1, NULL), "not NULL !");
    cr_assert_str_eq("toto", val1);
    cr_assert_str_eq("deuxieme", val2);
    cr_assert_str_eq("troisieme", val3);
    free_pile(nil);
    free_pile(value);
    free_pile(value2);
    free_pile(history);
    free(val1);
    free(val2);
    free(val3);
}

Test(quarantedeuxsh, load_history, .init = redirect_all_std)
{
    history_t *history = load_history();

    free_pile(history);
}

Test(strings, array_to_str, .init = redirect_all_std)
{
    char *array[] = {"1", "toto", "!!", NULL};

    cr_assert_str_eq("1 toto !!", array_to_str(array));
}

Test(strings, clean_str, .init = redirect_all_std)
{
    char *dirty = "  \t \t  ls -a\n";

    cr_assert_str_eq("ls -a", clean_str(dirty));
    cr_assert_null(clean_str(NULL), "not NULL !");
}

Test(strings, get_full_path, .init = redirect_all_std)
{
    cr_assert_null(get_full_path(NULL, NULL), "not NULL !");
    cr_assert_str_eq("toto/tata", get_full_path("toto", "tata"));
}

Test(strings, is_instr, .init = redirect_all_std)
{
    cr_assert(is_instr("str", 'c') == 0);
    cr_assert(is_instr("strc", 'c') == 1);
}

Test(strings, len_array, .init = redirect_all_std)
{
    char *array[] = {"1", "toto", "!!", NULL};

    cr_assert(my_len_array(NULL) == -1);
    cr_assert(my_len_array(array) == 3);
}

Test(strings, change_char, .init = redirect_all_std)
{
    char *str = strdup("t\toui\nt");
    char *str2 = strdup("'not ' sa");
    char *str3 = strdup("'not sa");

    if (!str)
        exit(84);
    cr_assert_str_eq("t oui t", my_str_change_char(str, "\tp\n", ' '));
    cr_assert_str_eq("'not 'psa", my_str_change_char(str2, " ", 'p'));
    cr_assert_null(my_str_change_char(str3, " ", 'p'), "not NULL !");
}

Test(strings, str_is_alphanum, .init = redirect_all_std)
{
    char *str = "t1G!";

    cr_assert(my_str_is_alphanum_and(str, '_') == 0);
    cr_assert(my_str_is_alphanum_and(str, '!') == 1);
}

Test(strings, push_tab, .init = redirect_all_std)
{
    char **tab = word_array("titi 't t' tutu", " ");

    if (!tab)
        exit(84);
    tab = my_push_tab(tab, "toto");
    cr_assert_str_eq("titi", tab[0]);
    cr_assert_str_eq("'t t'", tab[1]);
    cr_assert_str_eq("tutu", tab[2]);
    cr_assert_str_eq("toto", tab[3]);
    print_tab(tab);
    my_free_array(tab);
}

Test(strings, strndup, .init = redirect_all_std)
{
    char *str = my_strndup("hello world!", 6, 5);

    cr_assert_str_eq(str, "world");
}

Test(init, init_shell, .init = redirect_all_std)
{
    char *command[] = {"history", NULL};
    char *command2[] = {"history", "-c", NULL};
    mysh_t *mysh = init_shell(env);

    dump_history(mysh, command);
    dump_history(mysh, command2);
    free_shell(mysh);
}

Test(read, get_command_line, .init = redirect_all_std)
{
    cr_assert(get_command_line(NULL) == 0);
}

Test(create, create_ast, .init = redirect_all_std)
{
    ast_t *root = NULL;
    ast_t *or_test = NULL;
    ast_t *and_test = NULL;
    mysh_t *mysh = init_shell(env);
    char *line = strdup("ls; ls | cat -e > blue\n");
    char *line2 = strdup("ls || ls\n");
    char *line3 = strdup("ls && ls\n");

    bt_pprint(root);
    root = create_ast(line, root);
    or_test = create_ast(line2, or_test);
    and_test = create_ast(line3, and_test);
    bt_pprint(root);
    cr_assert(ast_or(or_test, mysh) == 0);
    cr_assert(ast_and(and_test, mysh) == 0);
    cr_assert_not_null(root, "NULL !");
}

Test(strings, get_arr_info, .init = redirect_all_std)
{
    char *arr[] = {"tablaeu", "de", "char", "chou", NULL};
    size_t size = 0;
    int len = 0;

    get_arr_info(arr, &len, &size);
    cr_assert(len == 4);
}

Test(env, setenv, .init = redirect_all_std)
{
    char **command = word_array("setenv toto titi", " \n");
    mysh_t *mysh = init_shell(env);
    
    mysh->env = my_setenv(mysh, command);
    cr_assert_not_null(mysh->env, "NULL !");
    cr_assert_null(my_setenv(mysh, NULL), "NULL !");
    free_shell(mysh);
}

Test(env, print_env, .init = redirect_all_std)
{
    mysh_t *mysh = init_shell(env);

    cr_assert_not_null(print_env(mysh), "NULL !");
}

Test(globing, handle_globbings, .init = redirect_all_std)
{
    mysh_t *mysh = init_shell(env);

    mysh->nline = strdup("ls *.c\n");
    cr_assert(handle_globbings(mysh) == 0);
}

Test(check, check_args, .init = redirect_all_std)
{
    cr_assert(check_parenthese("(ls -a)", ' ') == 0);
    cr_assert(check_parenthese("(ls -a))", ' ') == -1);
    cr_assert(check_parenthese("((ls -a)", ' ') == 1);
    cr_assert(check_double("lsO-aOO", 'O') == 1);
    cr_assert(check_double("lsO-aO", 'O') == 0);
}

Test(alias, unalias, .init = redirect_all_std)
{
    alias_t **alias = load_alias();
    char *line = "unalias ls";

    cr_assert_not_null(unalias(line, alias), "NULL !");
}

Test(alias, handle_alias, .init = redirect_all_std)
{
    mysh_t *mysh = init_shell(env);

    mysh->clean_line = strdup("ls\n");
    cr_assert(handle_alias(mysh) == 0);
}

Test(alias, verif_unalias, .init = redirect_all_std)
{
    mysh_t *mysh = init_shell(env);
    char *line = "unalias ls ll";

    cr_assert(verif_unalias(mysh, NULL) == 0);
    cr_assert(verif_unalias(mysh, "kdz efdizj edzip") == 0);
    cr_assert(verif_unalias(mysh, "unalias") == 1);
    cr_assert(verif_unalias(mysh, line) == 1);
}

Test(alias, verif_alias, .init = redirect_all_std)
{
    mysh_t *mysh = init_shell(env);
    char *line = "alias ls 'echo unitest sorry !'";

    cr_assert(verif_alias(mysh, "alias", mysh->alias) == 1);
    cr_assert(verif_alias(mysh, "jefh", mysh->alias) == 0);
    cr_assert(verif_alias(mysh, line, mysh->alias) == 1);
}

Test(local, set, .init = redirect_all_std)
{
    mysh_t *mysh = init_shell(env);
    char *command[] = {"set", "toto", "caca", NULL};

    cr_assert_not_null(mysh);
    cr_assert_not_null(my_set(mysh, command));
}

Test(unset, unset, .init = redirect_all_std)
{
    mysh_t *mysh = init_shell(env);
    char *command[] = {"unset", "?", NULL};

    cr_assert_not_null(my_unset(mysh, command));
}

Test(local, lget_cmd, .init = redirect_all_std)
{
    mysh_t *mysh = init_shell(env);

    mysh->nline = strdup("echo $?");
    lget_cmd(mysh);
    hget_cmd(mysh);
}

Test(error, get_error, .init = redirect_all_std)
{
    get_error(13, "ls");
    get_error(8, "ls");
}

Test(cd, change_dir, .init = redirect_all_std)
{
    mysh_t *mysh = init_shell(env);
    char *command[] = {"cd", "-", NULL};
    char *command2[] = {"cd", "..", NULL};

    cr_assert_not_null(change_dir(mysh, command));
    cr_assert_not_null(change_dir(mysh, command2));

}

Test(myrc, add_alias_to_file, .init = redirect_all_std)
{
    add_alias("toto", "titi");
    add_alias("toto", NULL);
}

Test(aadd, aadd_file, .init = redirect_all_std)
{
    mysh_t *mysh = init_shell(env);

    cr_assert_null(get_usr_clean(NULL, NULL));
    cr_assert_not_null(mysh->alias, "titi");
    cr_assert_not_null(aadd("   alias  nunu   'caca'", mysh->alias));
    cr_assert_not_null(aadd("   alias  nunu   'crcr'", NULL));
}

Test(back, handle_back, .init = redirect_all_std)
{
    char *cmd = strdup("cat -e `ls`");
    char *cmd2 = strdup("`ls`");
    int size = 4;

    cr_assert_not_null(bget_new_cmd(cmd, 2, "line1$line2$\n"));
    cr_assert_null(get_under_back(cmd, &size));
    cr_assert_not_null(get_under_back(cmd2, &size));
}

Test(which, bt, .init = redirect_all_std)
{
    mysh_t *mysh = init_shell(env);
    char **command = word_array("ls ls", " ");
    char **command2 = word_array("ls || ls", " ");
    char **command3 = word_array("ls 12 ls", " ");

    cr_assert(is_bt("env") == true);
    cr_assert(is_bt("edzj") == false);
    cr_assert_not_null(my_which(mysh, command));
    cr_assert_not_null(my_where(mysh, command2));
    cr_assert_not_null(my_repeat(mysh, command));
    cr_assert_not_null(my_repeat(mysh, command2));
    cr_assert_not_null(my_repeat(mysh, command3));
}
