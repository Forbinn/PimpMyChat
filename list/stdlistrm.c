/*
** stdlistrm.c for dll in /home/leroy_v/Epitech/linked_list/dll
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Nov 17 15:26:23 2012 vincent leroy
** Last update Mon Jun 10 20:48:14 2013 vincent leroy
*/

#include "stdlist.h"

int	list_pop_front(t_list *list, void (*freedata)(void*))
{
  t_elm	*rm;

  if (list == NULL || list->first == NULL)
  {
    errno = EINVAL;
    return (-1);
  }
  rm = list->first;
  list->nb_elm--;
  if (list->nb_elm == 0)
  {
    list->last = NULL;
    list->first = NULL;
    if (freedata != NULL)
      freedata(rm->data);
    free(rm);
    return (0);
  }
  list->first = rm->next;
  list->first->prev = list->last;
  list->last->next = list->first;
  if (freedata != NULL)
    freedata(rm->data);
  free(rm);
  return (0);
}

int	list_pop_back(t_list *list, void (*freedata)(void*))
{
  t_elm	*rm;

  if (list == NULL || list->last == NULL)
  {
    errno = EINVAL;
    return (-1);
  }
  rm = list->last;
  list->nb_elm--;
  if (list->nb_elm == 0)
  {
    list->last = NULL;
    list->first = NULL;
    if (freedata != NULL)
      freedata(rm->data);
    free(rm);
    return (0);
  }
  list->last = rm->prev;
  list->last->next = list->first;
  list->first->prev = list->last;
  if (freedata != NULL)
    freedata(rm->data);
  free(rm);
  return (0);
}

int	list_erase(t_list *list, int pos, void (*freedata)(void*))
{
  t_elm	*rm;

  if (list == NULL || pos >= list->nb_elm || pos < 0)
  {
    errno = EINVAL;
    return (-1);
  }
  if ((rm = list_get_elm(list, pos)) == NULL)
    return (-1);
  if (pos == 0)
    list->first = rm->next;
  else if (pos == list->nb_elm - 1)
    list->last = rm->prev;
  rm->next->prev = rm->prev;
  rm->prev->next = rm->next;
  if (freedata != NULL)
    freedata(rm->data);
  free(rm);
  list->nb_elm--;
  return (0);
}

int	list_clear(t_list *list, void (*freedata)(void*))
{
  int	res;

  if (list == NULL)
  {
    errno = EINVAL;
    return (-1);
  }
  while (list->nb_elm > 0)
    if ((res = list_pop_back(list, freedata)) != 0)
      return (res);
  return (0);
}
