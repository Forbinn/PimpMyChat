/*
** gui.h for  in /home/nathan/prog/epitech/rush/pimpmychat/PimpMyChat
** 
** Made by 
** Login   <nathan@epitech.net>
** 
** Started on  Sat Jun 15 12:38:19 2013 
** Last update Sat Jun 15 12:38:19 2013 
*/

#ifndef		GUI_H_
# define	GUI_H_

#include <ncurses.h>
#include <panel.h>
#include <form.h>
#include "x2p.h"

#define BUF_SIZE 4096

#define KEY_TAB 9

#define HEADER "XMPP CLIENT CURSES INTERFACE"
#define WIDTH COLS
#define HEIGHT LINES

typedef struct s_gui
{
  WINDOW *current_win;
  WINDOW *wins[3];
  PANEL *pans[3];
  PANEL *top;
} t_gui;

t_gui *init_gui(void);
int read_gui(t_gui *, t_data *);
void update(t_gui *);
void destroy_gui(void);

#endif		/* !GUI_H_*/
