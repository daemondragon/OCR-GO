#ifndef SHOW_CUTTING_H
#define SHOW_CUTTING_H

#include <gtk/gtk.h>
#include "info_word.h"

//Put red rectangle on each detected character
//matrix : assicied double matrix of the pixbuf
void frame_cut_characters(GdkPixbuf *input_pixbuf, double *matrix, W_list *list);

#endif
