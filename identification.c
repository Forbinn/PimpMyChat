/*
** identification.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 13:26:16 2013 vincent leroy
** Last update Sat Jun 15 13:30:08 2013 vincent leroy
*/

#include "x2p.h"

void send_msg(int fd, char *msg)
{
  write(fd, msg, strlen(msg));
}

char* make_msg(char *format, ...)
{
  static char buff[BUFF_SIZE];
  va_list ap;

  va_start(ap, format);
  vsnprintf(buff, BUFF_SIZE, format, ap);
  va_end(ap);
  return buff;
}

void send_header(char *ip, int sockfd)
{
  send_msg(sockfd, "<?xml version='1.0' encoding='UTF-8'?>");
  send_msg(sockfd, make_msg("<stream:stream xmlns:stream='http://etherx.jabber.org/streams' version='1.0' xmlns='jabber:client' to='%s' >", ip));
}
