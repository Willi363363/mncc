##
## EPITECH PROJECT, 2026
## Makefile
## File description:
## Makefile for mncc project
#
ifdef CICD
	CC = gcc
else
	CC = epiclang
endif

CFLAGS = -Iinclude -W -Wall -Werror -Wextra -g
LDFLAGS = -g
ifdef DEBUG
	CFLAGS += -g3
endif

NAME = mncc

SRC = $(shell find src -name '*.c')
SRC_OBJ = $(SRC:.c=.o)

MAIN = main.c
MAIN_OBJ = $(MAIN:.c=.o)

TESTS = unit_tests
TESTS_SRC = $(shell find tests -name '*.c')
TESTS_LDFLAGS = -lcriterion

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(SRC_OBJ) $(MAIN_OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(SRC_OBJ) $(MAIN_OBJ) *.gcno *.gcda *.gcov

fclean: clean
	$(RM) $(NAME) $(TESTS)

re: fclean all

$(TESTS): $(NAME)
	$(CC) $(CFLAGS) $(TESTS_LDFLAGS) $(TESTS_SRC) $(SRC) -o $@

tests_run: $(TESTS)
	./$(TESTS)

tests_re: clean tests_run

.PHONY: all clean fclean re
