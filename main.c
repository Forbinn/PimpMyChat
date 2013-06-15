/*
 ** main.c for PimpMyChat in /home/leroy_v/github/PimpMyChat
 **
 ** Made by vincent leroy
 ** Login  <leroy_v@epitech.eu>
 **
 ** Started on  Sat Jun 15 10:05:40 2013 vincent leroy
 ** Last update Sat Jun 15 10:19:42 2013 vincent leroy
 */

/*#include "x2p.h"*/

#include <gtk/gtk.h>

  int
main (int   argc,
    char *argv[])
{
  GtkWidget *window;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_show (window);

  gtk_main ();

  return 0;
}
