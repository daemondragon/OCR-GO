#ifndef OPTIONS_H
#define OPTIONS_H

#include<stdlib.h>
#include<gtk/gtk.h>
void on_quitter_btn(GtkWidget * widget, gpointer data);
void    create_file_selection();
void    get_way(GtkWidget *bouton,GtkWidget *file_selection);
void    test_xor();
void    cut_test();
void    test_filter();
void 	create_neuronal_network(GtkWidget * dialbox, GtkWidget * window);

#endif
