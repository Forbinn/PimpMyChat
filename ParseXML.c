/*
** ParseXML.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 13:11:57 2013 vincent leroy
** Last update Sat Jun 15 16:58:57 2013 vincent leroy
*/

#include "x2p.h"

void XML_Start(void *userData, const XML_Char *name, const XML_Char **atts)
{
  int i;
  t_data *data;

  data = userData;
  if (data->notif)
    strcpy(strncat(data->strNotif, name, BUFF_SIZE), "Error server reply: ");
  else if (strcmp(name, "stream:error") == 0)
    data->notif = 1;
  else
    data->notif = 0;

  i = 0;
  while (atts[i] != NULL)
  {
    if (strcmp(atts[i], "id") == 0 && atts[i + 1] != NULL)
      strcpy(data->id, atts[i + 1]);
    ++i;
  }
}

void XML_End(void *userData, const XML_Char *name)
{
  (void)userData;
  (void)name;
}

void XML_Character(void *userData, const XML_Char *s, int len)
{
  (void)userData;
  (void)s;
  (void)len;
}
