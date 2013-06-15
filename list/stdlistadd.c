/*
** stdlistadd.c for dll in /home/leroy_v/Epitech/linked_list/dll
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Nov 17 15:23:02 2012 vincent leroy
** Last update Thu Apr 25 15:56:29 2013 vincent leroy
*/

#include "stdlist.h"

int	list_push_front(t_list *list, void *data)
{
  t_elm	*elm;

  if (list == NULL)
  {
    errno = EINVAL;
    return (-1);
  }
  if ((elm = list_create_elm(data)) == NULL)
    return (-1);
  list->nb_elm++;
  if (list->nb_elm == 1)
  {
    list->first = elm;
    list->last = elm;
    elm->next = elm;
    elm->prev = elm;
    return (0);
  }
  list->first->prev = elm;
  elm->next = list->first;
  list->first = elm;
  list->last->next = elm;
  elm->prev = list->last;
  return (0);
}

int	list_push_back(t_list *list, void *data)
{
  t_elm	*elm;

  if (list == NULL)
  {
    errno = EINVAL;
    return (1);
  }
  if ((elm = list_create_elm(data)) == NULL)
    return (-1);
  list->nb_elm++;
  if (list->nb_elm == 1)
  {
    list->first = elm;
    list->last = elm;
    elm->next = elm;
    elm->prev = elm;
    return (0);
  }
  list->last->next = elm;
  elm->prev = list->last;
  list->last = elm;
  list->first->prev = elm;
  elm->next = list->first;
  return (0);
}

int	list_insert(t_list *list, void *data, int pos)
{
  t_elm	*elm;
  t_elm	*new;

  if (list == NULL || pos >= list->nb_elm || pos < 0)
  {
    errno = EINVAL;
    return (-1);
  }
  if (pos == list->nb_elm - 1)
    return (list_push_back(list, data));
  else if (pos == 0)
    return (list_push_front(list, data));
  if ((elm = list_get_elm(list, pos)) == NULL)
    return (-1);
  if ((new = list_create_elm(data)) == NULL)
    return (-1);
  new->prev = elm->prev;
  elm->prev->next = new;
  elm->prev = new;
  new->next = elm;
  list->nb_elm++;
  return (0);
}

int	list_iter(t_list *list, void (*function)(void*))
{
  t_elm	*actu;

  if (list == NULL || function == NULL)
  {
    errno = EINVAL;
    return (-1);
  }
  else if (list->first == NULL)
    return (0);
  actu = list->first;
  while (actu != list->last)
  {
    function(actu->data);
    actu = actu->next;
  }
  function(actu->data);
  return (0);
}

int	list_iter_param(t_list *list, void *param,
                        void (*function)(void*, void*))
{
  t_elm	*actu;

  if (list == NULL || function == NULL)
  {
    errno = EINVAL;
    return (-1);
  }
  else if (list->first == NULL)
    return (0);
  actu = list->first;
  while (actu != list->last)
  {
    function(actu->data, param);
    actu = actu->next;
  }
  function(actu->data, param);
  return (0);
}
