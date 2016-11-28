#ifndef OPTIONS_H
#define OPTIONS_H

#include<stdlib.h>
#include<gtk/gtk.h>
void on_quitter_btn(GtkWidget * widget, gpointer data);
void    create_file_selection();
void 	create_ner_selection();
void    get_way(GtkWidget *bouton,GtkWidget *file_selection);
void    test_xor();
void    cut_test();
void    test_filter();
void 	create_neuronal_network(GtkWidget * dialbox, GtkWidget * window);
void 	load_neural(GtkWidget * bout,GtkWidget * neural_selected);
void 	save_neural_net(GtkWidget * dialog,gpointer data);
void 	open_butt(GtkWidget *dialog,gpointer user_data);
void 	bin_button(GtkWidget * image);
#endif
