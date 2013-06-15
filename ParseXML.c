/*
** ParseXML.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 13:11:57 2013 vincent leroy
** Last update Sun Jun 16 00:20:59 2013 vincent leroy
*/

#include "x2p.h"

static int body;

void XML_Start(void *userData, const XML_Char *name, const XML_Char **atts)
{
  int i;
  char *slash;
  t_data *data;

  data = userData;
  if (data->notif.notif == 1)
  {
    strcpy(data->notif.strNotif, "Error server reply: ");
    strncat(data->notif.strNotif, name, BUFF_SIZE);
  }

  if (strcmp(name, "error") == 0)
    data->notif.notif = 1;
  else if (strcmp(name, "body") == 0)
  {
    body = 1;
    data->notif.notif = 2;
  }

  //fprintf(stderr, "Name: %s\n", name);
  i = 0;
  while (atts[i] != NULL)
  {
    //fprintf(stderr, "Attr[%d] = %s\n", i, atts[i]);
    if (strcmp(atts[i], "id") == 0 && atts[i + 1] != NULL)
      strcpy(data->id, atts[i + 1]);
    else if (strcmp(atts[i], "from") == 0 && atts[i + 1] != NULL)
    {
      if ((slash = strrchr(atts[i + 1], '/')) == NULL)
        strcpy(data->notif.sender, atts[i + 1]);
      else
        strncpy(data->notif.sender, atts[i + 1], slash - atts[i + 1]);
      //fprintf(stderr, "sender = %s\n", data->notif.sender);
    }
    ++i;
  }
}

void XML_End(void *userData, const XML_Char *name)
{
  (void)userData;
  if (strcmp(name, "body") == 0)
    body = 0;
}

void XML_Character(void *userData, const XML_Char *s, int len)
{
  t_data *data;

  data = userData;
  if (data->notif.notif == 2 && body)
  {
    strncpy(data->notif.strNotif, s, len);
    data->notif.strNotif[len] = 0;
    //fprintf(stderr, "data->notif : %s\n", data->notif.strNotif);
  }
}
