#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include "show_xor.h"
#include "testing_cut.h"
#include "filters.h"
#include "options.h"

typedef struct window_s
{
    GtkWidget           *main_window;
    neural_network_t    *net;
} window_t;

window_t*   create_window();
void        delete_window(window_t *window);

int     run_window(int argc, char **argv);
#endif
