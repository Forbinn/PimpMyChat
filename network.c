/*
** network.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:08:02 2013 vincent leroy
** Last update Sat Jun 15 22:55:02 2013 vincent leroy
*/

#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "x2p.h"

static XML_Parser p;

int connect_to_server(char *ip, char *port)
{
  int sockfd;
  struct protoent *proto;
  struct addrinfo *addr;
  struct addrinfo hints;

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
  if (connect(sockfd, addr->ai_addr, sizeof(struct sockaddr)) == -1)
  {
    freeaddrinfo(addr);
    return -1;
  }

  freeaddrinfo(addr);
  return sockfd;
}

void init_network(t_data *data)
{
  p = XML_ParserCreate(NULL);
  XML_SetElementHandler(p, &XML_Start, &XML_End);
  XML_SetCharacterDataHandler(p, &XML_Character);
  XML_SetUserData(p, data);
}

void destroy_network(t_data *data)
{
  close(data->sockfd);
  XML_ParserFree(p);
}

int readSocket(t_data *data)
{
  void *buff;
  int res;

  buff = XML_GetBuffer(p, BUFF_SIZE);
  if ((res = read(data->sockfd, buff, BUFF_SIZE)) > 0)
  {
    ((char*)buff)[res] = '\0';
    fprintf(stderr, "RECEIVED: %s\n", (char *) buff);
  }
  else if (res == 0)
  {
    data->notif.notif = 2;
    strcpy(data->notif.strNotif, "Deconnection");
    close(data->sockfd);
  }
  XML_ParseBuffer(p, res, res <= 0);

  return res;
}
