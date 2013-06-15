/*
** command.h for  in /home/nathan/prog/epitech/rush/pimpmychat/PimpMyChat
** 
** Made by 
** Login   <nathan@epitech.net>
** 
** Started on  Sat Jun 15 15:57:27 2013 
** Last update Sat Jun 15 15:57:27 2013 
*/

#ifndef		COMMAND_H_
# define	COMMAND_H_

#include <string.h>
#include "x2p.h"

typedef enum
{
  UNKNOWN_CMD,
  INVALID_CMD,
  OK_CMD,
  KO_CMD
} t_cmd_ret;

typedef t_cmd_ret (*cmd_handler)(char **params, t_data *data);

typedef struct s_cmd
{
  const char *name;
  char *usage;
  size_t nb_params;
  cmd_handler handler;
} t_cmd;

int handle_command(char *);

#endif		/* !COMMAND_H_*/
