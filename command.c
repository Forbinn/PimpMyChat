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
#include "connection.h"

static t_cmd_ret connect_handler(char **args, t_data *data)
{
  strncpy(data->ip, args[2], 20);
  data->username = strdup(args[1]);
  data->mdp = strdup(args[3]);
  init_connection(data);
  return (OK_CMD);
}

static t_cmd	commands[] =
{
  {"connect", "/connect login domain password", 4, connect_handler}
};

t_cmd_ret handle_command(char *cmd, t_data *data)
{
  size_t i;
  char *epur_cmd;
  char **args;

  epur_cmd = epur_str(cmd);
  args = array_from_string(epur_cmd, " \t");
  for (i = 0; i < sizeof(commands) / sizeof(t_cmd); i++)
  {
    if (strcmp(args[0], commands[i].name) == 0)
    {
      if (get_array_size(args) != commands[i].nb_params)
	return (INVALID_CMD);
      return commands[i].handler(args, data);
    }
  }
  /*free_string_array(args);*/
  return (UNKNOWN_CMD);
}
