/*
** network.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:08:02 2013 vincent leroy
** Last update Sat Jun 15 10:43:34 2013 vincent leroy
*/

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "x2p.h"

static int run;

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

pthread_t start_network(int *sockfd)
{
  pthread_t thread;

  if (pthread_create(&thread, NULL, &run_network, sockfd) != 0)
    return -1;
  run = 1;
  return thread;
}

void stop_network(pthread_t thread)
{
  run = 0;
  pthread_cancel(thread);
  pthread_join(thread, NULL);
}

void* run_network(void *data)
{
  int sockfd;
  int nb_char;
  char buff[BUFF_SIZE];

  sockfd = *(int*)data;
  while (run)
  {
    if ((nb_char = read(sockfd, buff, BUFF_SIZE)) < 0)
    {
      fprintf(stderr, "Error when read: %s\n", strerror(errno));
      run = 0;
    }
    else if (nb_char == 0)
    {
      printf("Deconnection from server\n");
      run = 0;
    }
    else
    {
      buff[nb_char] = '\0';
      printf("message receive: %s\n", buff);
    }
  }
  return data;
}
