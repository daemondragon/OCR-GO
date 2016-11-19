#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "show_xor.h"
#include "testing_cut.h"
#include "filters.h"
#include "options.h"
int     run_window(int argc, char **argv);
//void    on_quitter_btn(GtkWidget *pBtn, gpointer data);
void    create_file_selection();
void    get_way(GtkWidget *bouton,GtkWidget *file_selection);
void    test_xor();
void    cut_test();
void    test_filter();
#endif
