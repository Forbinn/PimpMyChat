/*
 ** gui.c for  in /home/nathan/prog/epitech/rush/pimpmychat/PimpMyChat
 ** 
 ** Made by 
 ** Login   <nathan@epitech.net>
 ** 
 ** Started on  Sat Jun 15 12:36:51 2013 
 ** Last update Sat Jun 15 12:36:51 2013 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gui.h"

/*static WINDOW *create_chat_win()*/
/*{*/
/*WINDOW *w;*/

/*w = newwin(HEIGHT, WIDTH, (LINES - HEIGHT) / 2, (COLS - WIDTH) / 2);*/
/*scrollok(w, TRUE);*/
/*box(w, 0, 0);*/
/*return w;*/
/*}*/

static WINDOW *create_connection_win()
{
  WINDOW *w;

  w = newwin(HEIGHT, WIDTH, (LINES - HEIGHT) / 2, (COLS - WIDTH) / 2);

  scrollok(w, TRUE);
  box(w, 0, 0);
  return w;
}

t_gui *init_gui(void)
{
  t_gui *gui;

  if ((gui = malloc(sizeof(t_gui))) == NULL)
    return (NULL);

  memset(gui->current_buffer, 0, BUF_SIZE);
  gui->buffer_id = 0;

  initscr();
  cbreak();
  /*noecho();*/
  keypad(stdscr, TRUE);
  /*raw();*/

  gui->wins[0] = create_connection_win();
  /*gui->wins[1] = create_chat_win();*/
  /*gui->wins[2] = create_chat_win();*/

  /*mvwprintw(gui->wins[0], 1, 1, "tototo\n");*/

  /*int i;*/
  /*for(i = 0; i < 3; ++i)*/
  /*box(gui->wins[i], 0, 0);*/

  gui->pans[0] = new_panel(gui->wins[0]);
  /*gui->pans[1] = new_panel(gui->wins[1]);*/
  /*gui->pans[2] = new_panel(gui->wins[2]);*/

  /*set_panel_userptr(gui->pans[0], gui->pans[1]);*/
  /*set_panel_userptr(gui->pans[1], gui->pans[2]);*/
  /*set_panel_userptr(gui->pans[2], gui->pans[0]);*/

  mvprintw(0, COLS / 2 - strlen(HEADER) / 2, "%s", HEADER);

  gui->top = gui->pans[0];
  update_panels();
  doupdate();
  return (gui);
}

void update(t_gui *gui)
{
  char line[4096] = {0};
  WINDOW *current_window;

  while (1)
  {
    current_window = panel_window(gui->top);
    wmove(current_window, LINES - 3, 1);
    whline(current_window, '-', WIDTH - 2);
    wmove(current_window, LINES - 2, 1);
    wgetstr(current_window, line);
    wmove(current_window, LINES - 2, 1);
    wclrtoeol(current_window);

    /*case KEY_TAB:*/
    /*gui->top = (PANEL *) panel_userptr(gui->top);*/
    /*top_panel(gui->top);*/
    /*break;*/
    update_panels();
    doupdate();
  }
}

void destroy(void)
{
  //supprimer fenetres
  //supprimer les formulaires
  endwin();
}
