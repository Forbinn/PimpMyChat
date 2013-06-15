/*
** ParseXML.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 13:11:57 2013 vincent leroy
** Last update Sat Jun 15 23:18:37 2013 vincent leroy
*/

#include "x2p.h"

void XML_Start(void *userData, const XML_Char *name, const XML_Char **atts)
{
  int i;
  t_data *data;

  data = userData;
  if (data->notif.notif == 1)
    strcpy(strncat(data->notif.strNotif, name, BUFF_SIZE), "Error server reply: ");

  if (strcmp(name, "error") == 0)
    data->notif.notif = 1;
  else if (strcmp(name, "body") == 0)
    data->notif.notif = 2;

  //fprintf(stderr, "Name: %s\n", name);
  i = 0;
  while (atts[i] != NULL)
  {
    //fprintf(stderr, "Attr[%d] = %s\n", i, atts[i]);
    if (strcmp(atts[i], "id") == 0 && atts[i + 1] != NULL)
      strcpy(data->id, atts[i + 1]);
    else if (strcmp(atts[i], "to") == 0 && atts[i + 1] != NULL)
      strcpy(data->notif.sender, atts[i + 1]);
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
  t_data *data;

  data = userData;
  if (data->notif.notif == 2)
    strncpy(data->notif.strNotif, s, len);
}
