##
## Makefile
##
## Made by vincent leroy
## Login   <leroy_v@epitech.eu>
##
## Started on  Sat Jun 15 10:03:40 2013 vincent leroy
## Last update Sat Jun 15 12:32:44 2013 vincent leroy
##

SRC		= main.c \
		  network.c \

NAME		= x2p

LIST		= list/

CFLAGS		= -Wall -Wextra -W -Werror
CFLAGS		+= -I$(LIST)

LDFLAGS		+= -L$(LIST) -llist

OBJ		= $(SRC:.c=.o)

RM		= rm -f

CC		= gcc

MAKE		= make -C

all: list $(NAME)

list:
	$(MAKE) $(LIST)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

clean:
	$(MAKE) $(LIST) clean
	$(RM) $(OBJ) *.swp *~ *#

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all list clean fclean re
