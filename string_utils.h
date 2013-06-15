/*
** string_utils.h for  in /home/nathan/prog/epitech/rush/pimpmychat/PimpMyChat
** 
** Made by 
** Login   <nathan@epitech.net>
** 
** Started on  Sat Jun 15 16:08:01 2013 
** Last update Sat Jun 15 16:08:01 2013 
*/

#ifndef		STRING_UTILS_H_
# define	STRING_UTILS_H_

#include <stdlib.h>
#include <string.h>

char *epur_str(char *);
char **array_from_string(char *, char *);
void free_string_array(char **);
size_t get_array_size(char **);

#endif		/* !STRING_UTILS_H_*/
