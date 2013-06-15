/*
** main.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:05:40 2013 vincent leroy
** Last update Sat Jun 15 14:05:59 2013 vincent leroy
*/

#include <signal.h>

#include "x2p.h"

void inter_sig(int signum)
{
  if (signum == SIGINT)
    stop();
}

int main()
{
  t_data data;

  signal(SIGINT, &inter_sig);
  memset(&data, 0, sizeof(t_data));
  data.ip = "10.18.207.43";
  if ((data.sockfd = connect_to_server(data.ip, "5222")) == -1)
  {
    fprintf(stderr, "Connection fail: %s\n", strerror(errno));
    return 1;
  }

  if (run(&data) == -1)
  {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return 1;
  }

  return 0;
}
