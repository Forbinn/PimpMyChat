/*
** stdlistaccess.c for list in /home/leroy_v/Epitech/list
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Mon Jun 10 20:18:38 2013 vincent leroy
** Last update Mon Jun 10 20:24:38 2013 vincent leroy
*/

#include "stdlist.h"

void*	list_front(t_list *list)
{
  if (list == NULL || list->first == NULL)
  {
    errno = EINVAL;
    return (NULL);
  }
  return (list->first->data);
}

void*	list_back(t_list *list)
{
  if (list == NULL || list->last == NULL)
  {
    errno = EINVAL;
    return (NULL);
  }
  return (list->last->data);
}

t_elm*	list_front_elm(t_list *list)
{
  if (list == NULL)
  {
    errno = EINVAL;
    return (NULL);
  }
  return (list->first);
}

t_elm*	list_back_elm(t_list *list)
{
  if (list == NULL)
  {
    errno = EINVAL;
    return (NULL);
  }
  return (list->last);
}
