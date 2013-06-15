/*
** stdlistsearch.c for dll in /home/leroy_v/Epitech/linked_list/dll
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Nov 17 17:39:13 2012 vincent leroy
** Last update Thu Apr 25 15:20:56 2013 vincent leroy
*/

#include "stdlist.h"

int	list_replace(t_list *list, void *data, int pos,
                     void (*freedata)(void*))
{
  int	res;

  if (list == NULL || pos >= list->nb_elm || pos < 0)
  {
    errno = EINVAL;
    return (-1);
  }
  if ((res = list_erase(list, pos, freedata)) != 0)
    return (res);
  return (list_insert(list, data, pos));
}

int	__search_loop_elm(t_list *list, t_elm *to_find)
{
  t_elm	*next;
  t_elm	*prev;
  int	i;
  int	j;

  next = list->first;
  prev = list->last;
  i = 0;
  j = list->nb_elm - 1;
  while (next != list->last)
  {
    if (next == to_find)
      return (i);
    else if (prev == to_find)
      return (j);
    next = next->next;
    if (next == prev)
      return (next == to_find ? i : -1);
    prev = prev->prev;
    i++;
    j--;
  }
  return (-1);
}

int	list_search_elm(t_list *list, t_elm *to_find)
{
  if (list == NULL || to_find == NULL)
  {
    errno = EINVAL;
    return (-2);
  }
  if (list->first == to_find)
    return (0);
  return (__search_loop_elm(list, to_find));
}

int	__search_loop_data(t_list *list, void *data_ref,
                           int (*cmp)(void*, void*))
{
  t_elm	*next;
  t_elm	*prev;
  int	i;
  int	j;

  next = list->first;
  prev = list->last;
  i = 0;
  j = list->nb_elm - 1;
  while (next != list->last)
  {
    if (cmp(next->data, data_ref) == 0)
      return (i);
    else if (cmp(prev->data, data_ref) == 0)
      return (j);
    next = next->next;
    if (next == prev)
      return (cmp(next->data, data_ref) == 0 ? i : -1);
    prev = prev->prev;
    i++;
    j--;
  }
  return (-1);
}

int	list_search_data(t_list *list, void *data_ref,
                         int (*cmp)(void*, void*))
{
  if (list == NULL || cmp == NULL)
  {
    errno = EINVAL;
    return (-2);
  }
  if (list->first == NULL)
    return (-1);
  if (cmp(list->first->data, data_ref) == 0)
    return (0);
  return (__search_loop_data(list, data_ref, cmp));
}
