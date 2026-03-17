##
## EPITECH PROJECT, 2026
## gcc
## File description:
## Makefile
##

ifdef CICD
	CC			=	gcc
else
	CC			=	epiclang
endif

CFLAGS		=	-Wall -Wextra $(INCLUDE)

ifdef DEBUG
	CFLAGS		+=	-g3

endif

INCLUDE		=	-I./include/

LIB	=	./lib/libmy.a	\
		./lib/ll.a

SRCF		=	src/

SRC			=	

OBJ			=	$(SRC:.c=.o)

NAME		=	./mncc

MAIN		=	$(SRCF)main.c

TEST_FILES	=	tests/tests.c

TEST_BIN	=	./unit_tests
TEST_FLAGS	=	--coverage -lcriterion

all:        $(NAME)

$(NAME): $(OBJ) $(MAIN)
	$(CC) $^ $(CFLAGS) -o $@

%o:            %.c
	$(CC) -c $< $(CFLAGS) -o $@
clean:
	$(RM) $(OBJ)

fclean:		clean
	make -f Makefile -C ./lib/my/ fclean
	make -f Makefile -C ./lib/linked_list/ fclean
	$(RM) $(NAME)

re:			fclean all

unit_tests:
	clang $(TEST_FILES) $(SRC) $(INCLUDE) $(TEST_FLAGS) -o $(TEST_BIN)

tests_run:	unit_tests
	$(TEST_BIN)

tests_clean: 
	rm -f ./unit_tests*

tests_re: tests_clean tests_run

.PHONY: all clean fclean re unit_tests tests_run tests_clean tests_re $(LIB)
