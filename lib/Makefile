NAME = libipes.a
CC = gcc
CFLAG = -c -Wall -Werror -Wextra -I inc
SRC_NAME = $(wildcard src/*.c)
OBJ_NAME = $(SRC_NAME:.c=.o)
AR = ar rc
RLIB = ranlib
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ_NAME)
	@$(AR) $(NAME) $(OBJ_NAME)
	@$(RLIB) $(NAME)

%.o: %.c
	@$(CC) $(CFLAG) $< -o $@

clean:
	@$(RM) $(OBJ_NAME)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
