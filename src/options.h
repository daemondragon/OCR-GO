#ifndef OPTIONS_H
#define OPTIONS_H

#include<stdlib.h>
#include<gtk/gtk.h>
void on_quitter_btn(GtkWidget * widget, gpointer data);
void    create_file_selection();
void 	create_ner_selection();
void    get_way(GtkWidget *bouton,GtkWidget *file_selection);
void 	create_neuronal_network(GtkWidget * dialbox, GtkWidget * window);
void 	load_neural(GtkWidget * bouton,GtkWidget * neural_selected);
void 	save_neural_net(GtkWidget * dialog,gpointer data);
void 	open_butt(GtkWidget *dialog,gpointer user_data);
void 	rotation_bout(char * image, gpointer data);
void 	binarize_op(GtkWidget* image, gpointer data);
#endif
