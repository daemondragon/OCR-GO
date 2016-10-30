#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <gtk/gtk.h>
int     run_window(int argc, char **argv);
void    on_quitter_btn(GtkWidget *pBtn, gpointer data);
void    creer_file_selection();
void    recuperer_chemin(GtkWidget *bouton, GtkWidget *file_selection);

#endif
