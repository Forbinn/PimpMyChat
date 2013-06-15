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
#include "gui.h"
#include "x2p.h"

typedef enum
{
  UNKNOWN_CMD,
  INVALID_CMD,
  NOT_CONNECTED,
  OK_CMD,
  KO_CMD
} t_cmd_ret;

typedef t_cmd_ret (*cmd_handler)(char **, t_data *, t_gui *);

typedef struct s_cmd
{
  const char *name;
  char *usage;
  size_t nb_params;
  cmd_handler handler;
  int connection_needed;
} t_cmd;

t_cmd_ret handle_command(char *, t_data *, t_gui *);

#endif		/* !COMMAND_H_*/
