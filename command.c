/*
** command.c for  in /home/nathan/prog/epitech/rush/pimpmychat/PimpMyChat
** 
** Made by 
** Login   <nathan@epitech.net>
** 
** Started on  Sat Jun 15 15:59:15 2013 
** Last update Sat Jun 15 15:59:15 2013 
*/

#include "command.h"

static t_cmd	commands[] =
{
  {"connect", "/connect login@domain password", 3, NULL}
};

int handle_command(char *cmd)
{
  size_t i;
  char *epur_cmd;
  char **args;

  epur_cmd = epur_str(cmd);
  free(cmd);
  args = array_from_string(epur_cmd, " \t");
  for (i = 0; i < sizeof(commands) / sizeof(t_cmd); i++)
  {
    if (strcmp(args[0], commands[i].name) == 0)
    {
      if (get_array_size(args) != commands[i].nb_params)
	return (INVALID_CMD);
      return commands[i].handler(args + 1, NULL);
    }
  }
  free_string_array(args);
  free(epur_cmd);
  return (UNKNOWN_CMD);
}
