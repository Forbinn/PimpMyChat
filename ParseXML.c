/*
** ParseXML.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 13:11:57 2013 vincent leroy
** Last update Sat Jun 15 14:05:31 2013 vincent leroy
*/

#include "x2p.h"

void XML_Start(void *userData, const XML_Char *name, const XML_Char **atts)
{
  int i;
  t_data *data;

  data = userData;
  printf("Start\n");
  printf("name = %s\n", name);
  i = 0;
  while (atts[i] != NULL)
  {
    printf("Atts: %s\n", atts[i]);
    if (strcmp(atts[i], "id") == 0 && atts[i + 1] != NULL)
      strcpy(data->id, atts[i + 1]);
    ++i;
  }
  printf("\n");
}

void XML_End(void *userData, const XML_Char *name)
{
  (void)userData;
  printf("End\n");
  printf("name = %s\n\n", name);
}

void XML_Character(void *userData, const XML_Char *s, int len)
{
  (void)userData;
  printf("Character\n");
  write(1, s, len);
  printf("\n\n");
}
