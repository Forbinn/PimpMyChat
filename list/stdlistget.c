/*
** stdlistget.c for list in /home/leroy_v/Epitech/list
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Thu Apr 25 15:05:58 2013 vincent leroy
** Last update Thu Apr 25 15:06:31 2013 vincent leroy
*/

#include "stdlist.h"

t_elm*	__get_elm_last(t_list *list, int pos)
{
  t_elm	*elm;
  int	i;

  i = 0;
  elm = list->last;
  while (elm != list->first)
  {
    if (i++ == (list->nb_elm - pos - 1))
      return (elm);
    elm = elm->prev;
  }
  return (NULL);
}

t_elm*	__get_elm_first(t_list *list, int pos)
{
  t_elm	*elm;
  int	i;

  i = 0;
  elm = list->first;
  while (elm != list->last)
  {
    if (i++ == pos)
      return (elm);
    elm = elm->next;
  }
  return (NULL);
}

t_elm*	list_get_elm(t_list *list, int pos)
{
  if (list == NULL || pos >= list->nb_elm || pos < 0)
  {
    errno = EINVAL;
    return (NULL);
  }
  else if (pos == list->nb_elm)
    return (list->last);
  else if (pos == 0)
    return (list->first);
  else if (pos >= list->nb_elm / 2)
    return (__get_elm_last(list, pos));
  else
    return (__get_elm_first(list, pos));
}

void*	list_get_data(t_list *list, int pos)
{
  t_elm	*elm;

  if ((elm = list_get_elm(list, pos)) == NULL)
    return (NULL);
  return (elm->data);
}
