##
## Makefile for libdlist in /home/leroy_v//Epitech/linked_list/dll
##
## Made by vincent leroy
## Login   <leroy_v@epitech.net>
##
## Started on  Mon Oct 22 09:15:22 2012 vincent leroy
## Last update Mon Jun 10 20:51:11 2013 vincent leroy
##

SRC	= stdlist.c \
	  stdlistget.c \
	  stdlistaccess.c \
	  stdlistadd.c \
	  stdlistrm.c \
	  stdlistsort.c \
	  stdlistsearch.c

NAME	= liblist.a

AR	= ar rc

RANLIB	= ranlib

CC	= gcc

OBJ	= $(SRC:.c=.o)

RM	= rm -f

CFLAGS	= -Wall -W -Wextra -Werror
CFLAGS	+= -O2 -s

all:	$(NAME)

$(NAME):	$(OBJ)
	$(AR) $(NAME) $(OBJ)
	$(RANLIB) $(NAME)

clean:
	$(RM) $(OBJ) *.swp *~ *#

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean fclean re
