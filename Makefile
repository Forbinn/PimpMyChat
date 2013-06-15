##
## Makefile
##
## Made by vincent leroy
## Login   <leroy_v@epitech.eu>
##
## Started on  Sat Jun 15 10:03:40 2013 vincent leroy
## Last update Sat Jun 15 10:28:42 2013 vincent leroy
##

SRC		= main.c \
		  network.c

NAME		= x2p

CFLAGS		= -Wall -Wextra -W -Werror

LDFLAGS		= -lpthread

OBJ		= $(SRC:.c=.o)

RM		= rm -f

CC		= gcc

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJ) *.swp *~ *#

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
