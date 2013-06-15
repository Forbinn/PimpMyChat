/*
** main.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:05:40 2013 vincent leroy
** Last update Sat Jun 15 12:32:28 2013 vincent leroy
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
  int sockfd;

  signal(SIGINT, &inter_sig);
  if ((sockfd = connect_to_server("10.18.207.43", "5222")) == -1)
  {
    fprintf(stderr, "Connection fail: %s\n", strerror(errno));
    return 1;
  }

  if (run(sockfd) == -1)
  {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return 1;
  }

  return 0;
}
