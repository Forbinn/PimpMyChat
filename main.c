/*
** main.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:05:40 2013 vincent leroy
** Last update Sat Jun 15 16:59:47 2013 vincent leroy
*/

#include <signal.h>

#include "gui.h"

static int run;

void inter_sig(int signum)
{
  if (signum == SIGINT)
    run = 0;
}

int main()
{
  t_gui *gui;
  t_data data;
  fd_set readfs;
  int ret;

  signal(SIGINT, &inter_sig);
  memset(&data, 0, sizeof(t_data));
  strncpy(data.ip, "10.18.207.43", 20);
  if ((data.sockfd = connect_to_server(data.ip, "5222")) == -1)
  {
    fprintf(stderr, "Connection fail: %s\n", strerror(errno));
    return 1;
  }

  init_network(&data);
  if ((gui = init_gui()) == NULL)
  {
    fprintf(stderr, "Failed to create GUI\n");
    return (1);
  }

  run = 1;
  while (run)
  {
    update(gui);

    FD_ZERO(&readfs);
    FD_SET(0, &readfs);
    FD_SET(data.sockfd, &readfs);

    if ((ret = select(data.sockfd + 1, &readfs, NULL, NULL, NULL)) == -1)
      run = 0;
    else
    {
      if (FD_ISSET(0, &readfs))
      {
	if (read_gui(gui, &data) == -1)
	{
	  run = 0;
	  ret = -1;
	}
      }
      if (FD_ISSET(data.sockfd, &readfs))
        if (readSocket(&data) == -1)
        {
          run = 0;
          ret = -1;
        }
    }
  }

  destroy_network();
  destroy_gui();

  if (ret == -1)
    fprintf(stderr, "Error: %s\n", strerror(errno));
  return 0;
}
