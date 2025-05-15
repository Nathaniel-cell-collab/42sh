##
## EPITECH PROJECT, 2025
## Makefile
## File description:
## Makefile for compiling mysh
##

CC      = gcc
SRC = $(shell find src -name '*.c' ! -name "main.c")
OBJ     = $(SRC:.c=.o)
NAME    = 42sh
CFLAGS  = -g3 -ggdb -Werror -Wall -Wextra -I ./include -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) src/main.c -o $(NAME) $(CFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -rf $(NAME) unit_tests
	rm -rf *.gc*

val: all
	valgrind ./$(NAME)

compile: all
	./$(NAME)

tests_run:
	$(CC) -o unit_tests $(SRC) tests/42sh_test.c $(CFLAGS)\
		--coverage -lcriterion -I ./include
	./unit_tests

cvrg:
	gcovr --exclude tests/

style: fclean
	coding-style .
	cat *.log
	rm -f *.log

memecheck: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./42sh

re: fclean all
