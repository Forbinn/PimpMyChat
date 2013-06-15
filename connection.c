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
  fprintf(stderr, "SEND HEADER\n");
  send_header(data);
  state = USERNAME;
}

void continue_connection(void)
{
  if (state == USERNAME)
  {
    fprintf(stderr, "SEND USERNAME\n");
    send_identifiant(conn_data);
    state = PASSWORD;
    return;
  }
  if (state == PASSWORD)
  {
    fprintf(stderr, "SEND Password\n");
    send_password(conn_data);
    state = CONNECTED;
    conn_data = NULL;
  }
}

int is_connected(void)
{
  return (state == CONNECTED);
}

int is_requested(void)
{
  return (state != NO_CONN);
}
