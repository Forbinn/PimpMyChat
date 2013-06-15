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
#include "stdlist.h"
#include "x2p.h"

#define BUF_SIZE 4096

#define KEY_TAB 9

#define HEADER "XMPP CLIENT CURSES INTERFACE"
#define WIDTH COLS
#define HEIGHT LINES

typedef struct s_window
{
  WINDOW *win;
  char receiver[BUF_SIZE];
} t_window;

typedef struct s_gui
{
  t_window *current_win;
  t_list *wins;
  t_list *pans;
  PANEL *top;
} t_gui;

t_gui *init_gui(void);
void add_win(t_gui *, char *);
void switch_win(t_gui *gui);
int read_gui(t_gui *, t_data *, int);
void update(t_gui *);
void destroy_gui(t_gui *);
int compare_window(void *, void *);

#endif		/* !GUI_H_*/
