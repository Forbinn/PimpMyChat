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
#include "command.h"
#include "gui.h"

static WINDOW *create_win()
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

  initscr();
  cbreak();
  /*noecho();*/
  keypad(stdscr, TRUE);
  /*raw();*/

  gui->wins[0] = create_win();
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
  gui->current_win = panel_window(gui->top);
  update_panels();
  doupdate();
  return (gui);
}

void read_gui(t_gui *gui)
{
  char line[BUF_SIZE] = {0};
  wgetstr(gui->current_win, line);

  if (line[0] == '/')
    handle_command(line);
}

void update(t_gui *gui)
{
  wmove(gui->current_win, LINES - 3, 1);
  whline(gui->current_win, '-', WIDTH - 2);
  wmove(gui->current_win, LINES - 2, 1);
  wmove(gui->current_win, LINES - 2, 1);
  wclrtoeol(gui->current_win);

  update_panels();
  doupdate();
}

void destroy(void)
{
  //supprimer fenetres
  endwin();
}
