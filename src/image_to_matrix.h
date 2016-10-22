#ifndef IMAGE_TO_MATRIX_H
#define IMAGE_TO_MATRIX_H

#include "image_to_matrix.h"
#include <gtk/gtk.h>

// input GdkPixbuf *pixbuf, double **matrix_end, int *pointer_width, int *pointer_height
// return an double array with grey_pixel vals , and the pointers vals
double *pixbuf_to_matrix_grey(GdkPixbuf *pixbuf, double **matrix_end, int *pointer_width, int *pointer_height );

// input file path const gchar *filename, double **matrix_end, int *pointer_width, int *pointer_height 
// return an double array with grey_pixel vals, and the pointers vals
double *file_to_matrix_grey(const char *filename, double **matrix_end, int *pointer_width, int *pointer_height );


#endif

