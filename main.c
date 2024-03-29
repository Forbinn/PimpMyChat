/*
** main.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:05:40 2013 vincent leroy
** Last update Sun Jun 16 11:21:00 2013 vincent leroy
*/

#include <signal.h>

#include "gui.h"

int run;

void inter_sig(int signum)
{
  if (signum == SIGINT)
    run = 0;
}

int main(int ac, char **av)
{
  t_gui *gui;
  t_data data;
  fd_set readfs;
  int ret;
  struct timeval timeout;

  if (ac < 2)
  {
    fprintf(stderr, "Usage: %s domain\n", av[0]);
    return 1;
  }

  signal(SIGINT, &inter_sig);
  memset(&data, 0, sizeof(t_data));
  strncpy(data.ip, av[1], 20);
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
    timeout.tv_sec = 0;
    timeout.tv_usec = 500000;

    if ((ret = select(data.sockfd + 1, &readfs, NULL, NULL, &timeout)) == -1)
      run = 0;
    else
    {
      if (FD_ISSET(0, &readfs) || ret == 0)
      {
	if (read_gui(gui, &data, ret) == -1)
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

  destroy_gui(&data, gui);
  destroy_network(&data);

  if (ret == -1)
    fprintf(stderr, "Error: %s\n", strerror(errno));
  return 0;
}
