##
## EPITECH PROJECT, 2017
##
## File description:
## makefile
##

NAME		= libminiparsearg.so

CC			= clang++

ARCHIVER	= ar

SRC			= src/MiniParseArg.cpp

TESTS_SRC	:= $(SRC)
TESTS_SRC	+= tests/MiniParseArg.cpp

OBJ			= $(SRC:.cpp=.o)
TESTS_OBJ	= $(TESTS_SRC:.cpp=.o)

RM			= rm -f

CXXFLAGS	= -Wall -Wextra -fPIC
CXXFLAGS	+= -I./include
LDFLAGS		= -shared

GREEN		= '\033[0;32m'
NO_COLOR	= '\033[0m'

%.o : %.cpp
	@$ $(CC) $(CXXFLAGS) -c $< -o $@
	@echo "$(CC) $(CXXFLAGS) -c $< -o $@ ["$(GREEN)"OK"$(NO_COLOR)"]"
.SUFFIXES: .o .cpp

all: $(NAME)

$(NAME): $(OBJ)
	@$ $(CC) $(LDFLAGS) $(OBJ) -o $@
	@echo "$(CC) $(LDFLAGS) $(OBJ) -o $@ \
	["$(GREEN)"LINKING OK"$(NO_COLOR)"]"

tests_run: $(TESTS_OBJ)
	@$ $(CC) -lcriterion $(TESTS_OBJ) -o $@
	@echo "$(CC) -lcriterion $(TESTS_OBJ) -o $@ \
	["$(GREEN)"LINKING OK"$(NO_COLOR)"]"
	./$@
	@$(RM) $@
	@$(RM) $(TESTS_OBJ)

debug: CFLAGS += -g3
debug: re

clean:
	$(RM) $(OBJ)
	$(RM) $(TESTS_OBJ)

fclean: clean
	$(RM) $(NAME) $(NAME:.so=.a)

re: fclean all

install: re
	@cp $(NAME) /usr/lib/$(NAME) 2> /dev/null || \
	printf "\033[1m\033[31mError : try sudo make install\033[0m\n" && \
	cp include/*.h /usr/include/ 2> /dev/null && \
	printf "\033[1m\033[32mLibrary successfull installed !\033[0m\n"

static: $(OBJ)
	$(ARCHIVER) rc $(NAME:.so=.a) $(OBJ)

.PHONY: all clean fclean re tests_run debug install static
