#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "show_xor.h"
#include "filters.h"
#include "options.h"
#include "testing_cut.h"
typedef struct window_s
{
    GtkWidget           *main_window;
    neural_network_t    *net;
    GtkWidget 		*table;
    GtkWidget 		*box;
   
   
} window_t;
typedef struct box_s
{
	GtkWidget 	*main_box;
	const gchar *image_name;
	GtkWidget 	*image;

} box_t;
window_t*   create_window();
box_t*	    create_box();
void        delete_window(window_t *window);

int     run_window(int argc, char **argv);
#endif
