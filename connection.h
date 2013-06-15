/*
** connection.h for  in /home/nathan/prog/epitech/rush/pimpmychat/PimpMyChat
** 
** Made by 
** Login   <nathan@epitech.net>
** 
** Started on  Sat Jun 15 18:09:45 2013 
** Last update Sat Jun 15 18:09:45 2013 
*/

#ifndef		CONNECTION_H_
# define	CONNECTION_H_

#include "x2p.h"

void init_connection(t_data *);
void continue_connection(void);
int is_connected(void);
int is_requested(void);

#endif		/* !CONNECTION_H_*/
