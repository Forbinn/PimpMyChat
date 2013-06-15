/*
** stdlist.h for dll in /home/leroy_v/Epitech/linked_list/dll
**
** Made by vincent leroy
** Login  <leroy_v@epitech.eu>
**
** Started on  Sat Nov 17 10:06:41 2012 vincent leroy
** Last update Mon Jun 10 20:25:37 2013 vincent leroy
*/

#ifndef STDLIST_H_
# define STDLIST_H_

#include <stdlib.h>
#include <errno.h>

/*
** lib de liste circulaire doublement chainee
*/

typedef struct	s_elm t_elm;
struct		s_elm
{
  void		*data;
  t_elm		*next;
  t_elm		*prev;
};

/*
** Les positions des elements vont de 0 a nb_elm - 1
** comme un tableau standard
*/

typedef struct	s_list t_list;
struct		s_list
{
  void		*data;
  int		nb_elm;
  t_elm		*first;
  t_elm		*last;

#ifdef _USE_LIST_FP
/*
** Autorise l'utilisation des pointeurs sur fonctions
** Peut etre lourd en memoire vue le nombre de pointeurs
*/
  int		(*size)(t_list*);
  void*		(*get_data)(t_list*, int);
  void*		(*front)(t_list*);
  void*		(*back)(t_list*);
  int		(*push_front)(t_list*, void*);
  int		(*push_back)(t_list*, void*);
  int		(*insert)(t_list*, void*, int);
  int		(*iter)(t_list*, void (*)(void*));
  int		(*iter_param)(t_list*, void*, void (*)(void*, void*));
  int		(*pop_front)(t_list*, void (*)(void*));
  int		(*pop_back)(t_list*, void (*)(void*));
  int		(*erase)(t_list*, int, void (*)(void*));
  int		(*clear)(t_list*, void (*)(void*));
  int		(*replace)(t_list*, void*, int, void (*)(void*));
  int		(*search_data)(t_list*, void*, int (*)(void*, void*));
  int		(*sort)(t_list*, int, int (*)(void*, void*));
#endif
};

/*
** retour des fonctions :
**
** les fonctions renvoient 0 si tout est OK
** sinon elles renvoient -1 et errno est
** 'setter' à la bonne valeur
**
** Attention:
** Les fonctions de recherche renvoient -1 si elles n'ont rient trouvees
** et -2 si il y a une erreur
**
** Pour les fonctions qui renvoient un pointeur :
** elles renvoient NULL si il y a un probleme
*/

/*
** stdlist.c
*/
t_list*	list_create(void *data);
t_elm*	list_create_elm(void *data);
int	list_delete(t_list *list, void (*freelist)(void*),
                                  void (*freedata)(void*));
int	list_size(t_list *list);
/*
** stdlistget.c
*/
t_elm*	list_get_elm(t_list *list, int pos);
void*	list_get_data(t_list *list, int pos);
/*
** stdlistaccess.c
*/
void*	list_front(t_list *list);
void*	list_back(t_list *list);
t_elm*	list_front_elm(t_list *list);
t_elm*	list_back_elm(t_list *list);
/*
** stdlistadd.c
*/
int	list_push_front(t_list *list, void *data);
int	list_push_back(t_list *list, void *data);
int	list_insert(t_list *list, void *data, int pos);
int	list_iter(t_list *list, void (*function)(void*));
int	list_iter_param(t_list *list, void *param,
                        void (*function)(void*, void*));
/*
** stdlistrm.c
*/
int	list_pop_front(t_list *list, void (*freedata)(void*));
int	list_pop_back(t_list *list, void (*freedata)(void*));
int	list_erase(t_list *list, int pos, void (*freedata)(void*));
int	list_clear(t_list *list, void (*freedata)(void*));
/*
** stdlistsearch.c
*/
int	list_replace(t_list *list, void *data, int pos,
                     void (*freedata)(void*));
int	list_search_elm(t_list *list, t_elm *to_find);
int	list_search_data(t_list *list, void *data_ref,
                         int (*cmp)(void*, void*));
/*
** stdlistsort.c
*/
int	list_sort(t_list *list, int abc, int (*cmp)(void*, void*));

#endif /* !STDLIST_H_ */
