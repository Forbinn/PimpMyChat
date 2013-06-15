/*
** network.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:08:02 2013 vincent leroy
** Last update Sat Jun 15 13:30:46 2013 vincent leroy
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

int run(int sockfd, char *ip)
{
  fd_set readfs;
  XML_Parser p;
  int res;

  p = XML_ParserCreate(NULL);
  XML_SetElementHandler(p, &XML_Start, &XML_End);
  XML_SetCharacterDataHandler(p, &XML_Character);
  send_header(ip, sockfd);
  r = 1;
  while (r)
  {
    FD_ZERO(&readfs);
    FD_SET(0, &readfs);
    FD_SET(sockfd, &readfs);

    if ((res = select(sockfd + 1, &readfs, NULL, NULL, NULL)) == -1 && errno != EINTR)
      r = 0;
    else if (res > 0)
      r = check_readfs(&readfs, sockfd, p);
  }
  XML_ParserFree(p);

  return res;
}

int check_readfs(fd_set *readfs, int sockfd, XML_Parser p)
{
  t_msg msg;
  int res;
  void *buff;

  if (FD_ISSET(0, readfs))
  {
    res = read(0, msg.msg, BUFF_SIZE);
    write(sockfd, msg.msg, res);
  }
  if (FD_ISSET(sockfd, readfs))
  {
    buff = XML_GetBuffer(p, BUFF_SIZE);
    if ((res = read(sockfd, buff, BUFF_SIZE)) > 0)
    {
      ((char*)buff)[res] = '\0';
      printf("buff = %s\n", (char*)buff);
    }
    else if (res == 0)
      printf("Deconnection\n");
    XML_ParseBuffer(p, res, res <= 0);

    return res > 0;
  }

  return 1;
}
