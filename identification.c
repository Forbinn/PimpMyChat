/*
** identification.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 13:26:16 2013 vincent leroy
** Last update Sat Jun 15 14:46:27 2013 vincent leroy
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

void send_header(t_data *data)
{
  send_msg(data->sockfd, "<?xml version='1.0' encoding='UTF-8'?>");
  send_msg(data->sockfd, make_msg("<stream:stream xmlns:stream='http://etherx.jabber.org/streams' version='1.0' xmlns='jabber:client' to='%s' >", data->ip));
}

void send_identifiant(t_data *data)
{
  send_msg(data->sockfd, make_msg("<iq type='get' id='%s' to='%s' ><query xmlns='jabber:iq:auth'><username>%s</username></query></iq>", data->id, data->ip, data->username));
}

void send_password(t_data *data)
{
  send_msg(data->sockfd, make_msg("<iq type='set' id='%s' to='%s' ><query xmlns='jabber:iq:auth'><username>%s</username><password>%s</password></query></iq>", data->id, data->ip, data->username, data->mdp));
}

void send_deconnection(t_data *data)
{
  send_msg(data->sockfd, "</stream:stream>");
}

void send_newstate(t_data *data, char *msgState)
{
  char *buff;

  switch (data->state)
  {
    case TYPE_AWAY: buff = "away"; break;
    case TYPE_CHAT: buff = "chat"; break;
    case TYPE_DND: buff = "dnd"; break;
    case TYPE_XA: buff = "xa"; break;
    default: buff = "";
  }
  send_msg(data->sockfd, make_msg("<presence><show>%s</show><status>%s</status></presence>", buff, msgState));
}

void send_chatmessage(t_data *data, char *msg, char *dest)
{
  send_msg(data->sockfd, make_msg("<message to='%s' type='chat'><body>%s</body></message>", dest, msg));
}

void send_normalmessage(t_data *data, char *subject, char *msg, char *dest)
{
  send_msg(data->sockfd, make_msg("<message to='%s' type='normal'><subject>%s</subject><body>%s</body></message>", dest, subject, msg));
}
