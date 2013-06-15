/*
** network.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:08:02 2013 vincent leroy
** Last update Sat Jun 15 12:29:44 2013 vincent leroy
*/

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "x2p.h"

static int r;

int connect_to_server(char *ip, char *port)
{
  int sockfd;
  struct protoent *proto;
  struct addrinfo *addr;
  struct addrinfo hints;
  struct sockaddr_in *sin;

  if ((proto = getprotobyname("TCP")) == NULL)
    return -1;
  if ((sockfd = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    return -1;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = proto->p_proto;

  if (getaddrinfo(ip, port, &hints, &addr) != 0)
    return -1;
  printf("Waiting for connection...\n");
  if (connect(sockfd, addr->ai_addr, sizeof(struct sockaddr)) == -1)
  {
    freeaddrinfo(addr);
    return -1;
  }

  sin = (struct sockaddr_in*)addr->ai_addr;
  printf("Connection established with the server %s (%s) on port %d\n", ip, inet_ntoa(sin->sin_addr), ntohs(sin->sin_port));
  freeaddrinfo(addr);

  return sockfd;
}

void stop()
{
  r = 0;
}

int run(int sockfd)
{
  fd_set readfs;
  int res;

  r = 1;
  while (r)
  {
    FD_ZERO(&readfs);
    FD_SET(0, &readfs);
    FD_SET(sockfd, &readfs);

    if ((res = select(sockfd + 1, &readfs, NULL, NULL, NULL)) == -1 && errno != EINTR)
      r = 0;
    else if (res > 0)
      r = check_readfs(&readfs, sockfd);
  }
  return res;
}

int check_readfs(fd_set *readfs, int sockfd)
{
  t_msg msg;

  if (FD_ISSET(0, readfs))
  {
    read(0, msg.msg, BUFF_SIZE);
    printf("read fd 0: %s\n", msg.msg);
  }
  if (FD_ISSET(sockfd, readfs))
  {
    if (read(sockfd, msg.msg, BUFF_SIZE) <= 0)
    {
      printf("Deconnection\n");
      return 0;
    }
    else
      printf("read sockfd %d: %s\n", sockfd, msg.msg);
  }

  return 1;
}
