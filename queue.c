/*
** queue.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Jun 15 10:45:59 2013 vincent leroy
** Last update Sat Jun 15 11:03:08 2013 vincent leroy
*/

#include "x2p.h"

static t_list *queue;
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int create_queue()
{
  if ((queue = list_create(NULL)) == NULL)
    return -1;
  return 0;
}

void delete_queue()
{
  list_delete(queue, NULL, &free);
}

void add_message(t_msg *msg)
{
  pthread_mutex_lock(&mutex);
  list_push_back(queue, msg);
  pthread_mutex_unlock(&mutex);
}

t_msg* get_message()
{
  t_msg *msg = NULL;

  pthread_mutex_lock(&mutex);
  if (list_size(queue) > 0)
  {
    msg = list_front(queue);
    list_pop_front(queue, NULL);
  }
  pthread_mutex_unlock(&mutex);
  return msg;
}

int queue_size()
{
  int size;

  pthread_mutex_lock(&mutex);
  size = list_size(queue);
  pthread_mutex_unlock(&mutex);
  return size;
}
