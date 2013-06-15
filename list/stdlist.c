/*
** stdlist.c for dll in /home/leroy_v/Epitech/linked_list/dll
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Nov 17 10:10:11 2012 vincent leroy
** Last update Mon Jun 10 20:26:09 2013 vincent leroy
*/

#include "stdlist.h"

t_list*		list_create(void *data)
{
  t_list	*list;

  if ((list = calloc(1, sizeof(t_list))) == NULL)
    return (NULL);
  list->data = data;
#ifdef _USE_LIST_FP
  list->size = &list_size;
  list->get_data = &list_get_data;
  list->front = &list_front;
  list->back = &list_back;
  list->push_front = &list_push_front;
  list->push_back = &list_push_back;
  list->insert = &list_insert;
  list->iter = &list_iter;
  list->iter_param = &list_iter_param;
  list->pop_front = &list_pop_front;
  list->pop_back = &list_pop_back;
  list->erase = &list_erase;
  list->clear = &list_clear;
  list->replace = &list_replace;
  list->search_data = &list_search_data;
  list->sort = &list_sort;
#endif
  return (list);
}

t_elm*	list_create_elm(void *data)
{
  t_elm	*elm;

  if ((elm = calloc(1, sizeof(t_elm))) == NULL)
    return (NULL);
  elm->data = data;
  return (elm);
}

int	list_delete(t_list *list, void (*freelist)(void*),
                                  void (*freedata)(void*))
{
  if (list == NULL)
  {
    errno = EINVAL;
    return (-1);
  }
  if (list_clear(list, freedata) != 0)
    return (-1);
  if (freelist != NULL)
    freelist(list->data);
  free(list);
  return (0);
}

int	list_size(t_list *list)
{
  if (list == NULL)
  {
    errno = EINVAL;
    return (-1);
  }
  return (list->nb_elm);
}
