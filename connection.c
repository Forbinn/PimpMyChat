/*
** connection.c for  in /home/nathan/prog/epitech/rush/pimpmychat/PimpMyChat
** 
** Made by 
** Login   <nathan@epitech.net>
** 
** Started on  Sat Jun 15 18:08:46 2013 
** Last update Sat Jun 15 18:08:46 2013 
*/

#include <stdio.h>
#include "command.h"
#include "connection.h"

static t_conn_state state = NO_CONN;
static t_data *conn_data = NULL;

void init_connection(t_data *data)
{
  conn_data = data;
  send_header(data);
  state = USERNAME;
}

void continue_connection(void)
{
  if (state == USERNAME)
  {
    send_identifiant(conn_data);
    state = PASSWORD;
  }
  else if (state == PASSWORD)
  {
    send_password(conn_data);
    state = CONNECTED;
  }
  else if (state == CONNECTED)
  {
    conn_data->state = TYPE_CHAT;
    send_newstate(conn_data, "YO GROS");
    state = AUTHENTIFIED;
    conn_data = NULL;
  }
}

int is_authentified(void)
{
  return (state == AUTHENTIFIED);
}

int is_requested(void)
{
  return (state != NO_CONN);
}
