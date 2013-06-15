/*
** string_utils.c for  in /home/nathan/prog/epitech/my_irc/myirc-2016-allebe_k/server
** 
** Made by 
** Login   <nathan@epitech.net>
** 
** Started on  Wed Apr 24 18:01:59 2013 
** Last update Wed Apr 24 18:01:59 2013 
*/

#define _XOPEN_SOURCE 700

#include "string_utils.h"

static int is_space(char c)
{
  if (c == ' ' || c == '\t')
    return (1);
  return (0);
}

char *epur_str(char *str)
{
  char *new;
  int begin;
  int i;
  int j;

  new = malloc(sizeof(char) * strlen(str) + 1);
  if (new == NULL) return (NULL);
  begin = 1;
  for (i = 0, j = 0 ; str[i] ; )
  {
    for ( ; str[i] && is_space(str[i]) ; i++);
    if (!begin && str[i])
    {
      new[j] = ' ';
      j++;
    }
    for (; str[i] && !is_space(str[i]); i++, j++)
    {
      begin = 0;
      new[j] = str[i];
    }
  }
  new[j] = '\0';
  return (new);
}

char **array_from_string(char *str, char *delims)
{
  char **tab;
  char *token;
  char *tmp;
  size_t i;
  size_t size;

  size = 0;
  i = 0;
  tmp = strdup(str);
  while (strtok((!i) ? tmp : NULL, delims) != NULL)
  {
    i++;
    size++;
  }
  free(tmp);
  if ((tab = malloc(sizeof(char *) * (size + 1))) == NULL)
    return (NULL);
  i = 0;
  while ((token = strtok((!i) ? str : NULL, delims)) != NULL)
  {
    tab[i] = token;
    i++;
  }
  tab[i] = NULL;
  return (tab);
}

void free_string_array(char **array)
{
  int i;

  i = 0;
  while (array[i])
  {
    free(array[i]);
    i++;
  }
}

size_t get_array_size(char **array)
{
  size_t i;

  i = 0;
  while (array[i])
    i++;
  return (i);
}
