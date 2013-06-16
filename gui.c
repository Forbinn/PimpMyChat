/*
 ** gui.c for  in /home/nathan/prog/epitech/rush/pimpmychat/PimpMyChat
 *data->* 
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
#include "connection.h"
#include "x2p.h"
#include "gui.h"

static void free_window(void *data)
{
  t_window *win = data;

  list_delete(win->msgs, NULL, &free);
  delwin(win->win);
  free(win);
}

static void display_messages(t_gui *gui)
{
  int i;
  char *msg;

  for (i = 0; i < list_size(gui->current_win->msgs); i++)
  {
    msg = list_get_data(gui->current_win->msgs, i);
    mvwprintw(gui->current_win->win, 2 + i, 2, "%s", msg);
  }
}

static void push_message(char *msg, t_window *win)
{
  if (list_size(win->msgs) > LINES - 5)
    list_pop_front(win->msgs, &free);
  list_push_back(win->msgs, msg);
}

static void display_convers(t_gui *gui)
{
  int i;
  t_window *w;
  t_window *main_win = (t_window *) list_front(gui->wins);

  wattron(main_win->win, COLOR_PAIR(2));
  mvwprintw(main_win->win, 3, 2, "Current conversations:");
  wattroff(main_win->win, COLOR_PAIR(2));
  for (i = 0; i < list_size(gui->wins); i++)
  {
    w = list_get_data(gui->wins, i);
    /*push_message(w->receiver, list_front(gui->wins));*/
    mvwprintw(main_win->win, 4 + i, 2, "%s", w->receiver);
  }
}

int compare_nick(void *data, void *data_ref)
{
  t_window *window = data;
  char *nick = data_ref;
  char *c;

  if ((c = strrchr(nick, '/')) == NULL)
    return (strcmp(window->receiver, nick));
  return (strncmp(window->receiver, nick, c - nick));
}

int compare_window(void *data, void *data_ref)
{
  t_window *window = data;

  return (window->win == data_ref) ? 0 : 1;
}

void add_win(t_gui *gui, char *receiver, int type)
{
  t_window *window;
  WINDOW *w;

  w = newwin(HEIGHT, WIDTH, (LINES - HEIGHT) / 2, (COLS - WIDTH) / 2);


  wbkgd(w, COLOR_PAIR(1));

  scrollok(w, TRUE);
  box(w, 0, 0);
  window = calloc(1, sizeof(t_window));
  window->win = w;
  window->type = type;
  window->msgs = list_create(NULL);
  if (receiver != NULL)
  {
    strncpy(window->receiver, receiver, BUF_SIZE);

    char header[BUF_SIZE];
    int n = snprintf(header, BUF_SIZE, "RECEIVER: %s", receiver);
    wmove(w, 1, COLS / 2 - n / 2);
    wprintw(w, header, receiver);
  }
  else
  {
    wattron(w, COLOR_PAIR(2));
    wmove(w, 2, COLS / 2 - strlen("COUCOU JE SUIS LA FENETRE PRINCIPALE") / 2);
    wprintw(w, "COUCOU JE SUIS LA FENETRE PRINCIPALE");
    wattroff(w, COLOR_PAIR(2));
  }

  list_push_back(gui->wins, window);
  PANEL *p = new_panel(w);
  set_panel_userptr(list_back(gui->pans), p);
  set_panel_userptr(p, list_front(gui->pans));
  list_push_back(gui->pans, p);
}

void handle_notif(t_gui *gui, t_data *data)
{
  t_window *w;

  /*fprintf(stderr, "HANDLE NOTIF FROM: [%s] [%s]\n", data->notif.sender, data->notif.strNotif);*/
  int pos;
  pos = list_search_data(gui->wins, data->notif.sender, &compare_nick);
  if (pos != -1)
    w = list_get_data(gui->wins, pos);
  else
  {
    char cmd[BUF_SIZE];

    snprintf(cmd, BUF_SIZE, "chat %s", data->notif.sender);
    handle_command(cmd, data, gui);
    pos = list_search_data(gui->wins, data->notif.sender, &compare_nick);
    /*fprintf(stderr, "POS VALUE = %d\n", pos);*/
    if (pos != -1)
      w = list_get_data(gui->wins, pos);
    else
      return;
  }

  char msg[BUF_SIZE];

  snprintf(msg, BUF_SIZE, "%s: %s", data->notif.sender, data->notif.strNotif);
  push_message(strdup(msg), w);

  if (w == gui->current_win)
  {
    display_messages(gui);
    refresh();
    update_panels();
    doupdate();
  }
}

void switch_win(t_gui *gui)
{
  gui->top = panel_userptr(gui->top);
  top_panel(gui->top);

  int pos;
  pos = list_search_data(gui->wins, panel_window(gui->top), &compare_window);
  if (pos != -1)
  {
    gui->current_win = list_get_data(gui->wins, pos);
    if (gui->current_win->type == CHAT_WINDOW)
      display_messages(gui);
    else if (gui->current_win->type == MAIN_WINDOW)
    {
      display_convers(gui);
    }
  }
  refresh();
  update_panels();
  doupdate();
}

t_gui *init_gui(void)
{
  t_gui *gui;

  if ((gui = malloc(sizeof(t_gui))) == NULL)
    return (NULL);

  gui->wins = list_create(NULL);
  gui->pans = list_create(NULL);

  initscr();
  cbreak();
  /*noecho();*/
  keypad(stdscr, TRUE);
  /*raw();*/

  start_color();			/* Start color 			*/
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  init_pair(2, COLOR_BLUE, COLOR_WHITE);
  init_pair(3, COLOR_WHITE, COLOR_RED);

  add_win(gui, NULL, MAIN_WINDOW);

  /*gui->wins[1] = create_chat_win();*/
  /*gui->wins[2] = create_chat_win();*/


  /*int i;*/
  /*for(i = 0; i < 3; ++i)*/
  /*box(gui->wins[i], 0, 0);*/

  /*gui->pans[1] = new_panel(gui->wins[1]);*/
  /*gui->pans[2] = new_panel(gui->wins[2]);*/

  /*set_panel_userptr(gui->pans[0], gui->pans[1]);*/
  /*set_panel_userptr(gui->pans[1], gui->pans[2]);*/
  /*set_panel_userptr(gui->pans[2], gui->pans[0]);*/

  /*mvprintw(0, COLS / 2 - strlen(HEADER) / 2, "%s", HEADER);*/

  int pos;

  gui->top = list_front(gui->pans);
  pos = list_search_data(gui->wins, panel_window(gui->top), &compare_window);
  if (pos != -1)
    gui->current_win = list_get_data(gui->wins, pos);

  /*wmove(gui->current_win->win, LINES - 2, 1);*/

  update_panels();
  doupdate();
  return (gui);
}

int read_gui(t_gui *gui, t_data *data, int ret)
{
  char line[BUF_SIZE] = {0};

  if (!is_requested() || is_authentified())
  {
    if (is_authentified())
    {
      if (data->notif.notif)
      {
	handle_notif(gui, data);
	data->notif.notif = 0;
      }
    }
    if (ret)
    {
      wmove(gui->current_win->win, LINES - 2, 1);
      if (wgetstr(gui->current_win->win, line) == ERR)
	return -1;
      if (line[0] == '/')
      {
	handle_command(line + 1, data, gui);
      }
      else if (is_authentified() && gui->current_win != list_front(gui->wins))
      {
	char msg[BUF_SIZE];

	snprintf(msg, BUF_SIZE, "%s: %s", data->username, line);
	push_message(strdup(msg), gui->current_win);
	send_chatmessage(data, line, gui->current_win->receiver);
	display_messages(gui);
	refresh();
	update_panels();
	doupdate();
      }
    }
  }
  else
  {
    continue_connection();
  }
  return 0;
}

void update(t_gui *gui)
{
  wmove(gui->current_win->win, LINES - 3, 1);
  whline(gui->current_win->win, '-', WIDTH - 2);
  wmove(gui->current_win->win, LINES - 2, 1);
  wclrtoeol(gui->current_win->win);

  update_panels();
  doupdate();
}

void destroy_gui(t_data *data, t_gui *gui)
{
  list_delete(gui->pans, NULL, (void (*)(void *)) &del_panel);
  list_delete(gui->wins, NULL, &free_window);
  endwin();
  send_deconnection(data);
}
