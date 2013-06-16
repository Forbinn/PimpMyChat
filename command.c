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

extern int run;

static t_cmd_ret quit_handler(char **args, t_data *data, t_gui *gui)
{
  (void) args;
  (void) data;

  if (gui->current_win->type == MAIN_WINDOW)
  {
    run = 0;
  }
  return (OK_CMD);
}

static t_cmd_ret connect_handler(char **args, t_data *data, t_gui *gui)
{
  (void) args;
  (void) data;
  (void) gui;

  /*(void) gui;*/
  /*strncpy(data->ip, args[2], 20);*/
  /*data->username = strdup(args[1]);*/
  /*data->mdp = strdup(args[3]);*/
  /*init_connection(data);*/
  data->username = strdup("zizi4242");
  data->mdp = strdup("zizi4242");
  init_connection(data);
  return (OK_CMD);
}

static t_cmd_ret next_handler(char **args, t_data *data, t_gui *gui)
{
  (void) args;
  (void) data;

  switch_win(gui);
  return (OK_CMD);
}

static t_cmd_ret chat_handler(char **args, t_data *data, t_gui *gui)
{
  int pos;

  pos = list_search_data(gui->wins, args[1], &compare_nick);
  if (pos == -1)
  {
    add_win(gui, args[1], CHAT_WINDOW);
    next_handler(NULL, data, gui);
  }
  return (OK_CMD);
}

static t_cmd	commands[] =
{
  {"connect", "/connect login domain password", 1, connect_handler, 0},
  {"chat", "/chat login@domain", 2, chat_handler, 1},
  {"next", "/next", 1, next_handler, 0},
  {"quit", "/quit", 1, quit_handler, 0}
};

t_cmd_ret handle_command(char *cmd, t_data *data, t_gui *gui)
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
      if (commands[i].connection_needed && !is_authentified())
	return (NOT_CONNECTED);
      return commands[i].handler(args, data, gui);
    }
  }
  /*free_string_array(args);*/
  return (UNKNOWN_CMD);
}
