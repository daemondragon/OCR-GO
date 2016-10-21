#ifndef IMAGE_TO_MATRIX_H
#define FEED_FORWARD_H

#include "image_to_matrix.h"

// input GdkPixbuf *pixbuf, double **matrix_end, int *pointer_width, int *pointer_height
// return an double array with grey_pixel vals , and the pointers vals
double * pixbuf_to_matrix(GdkPixbuf *pixbuf, double **matrix_endint, *pointer_width, int *pointer_height );

// input file path const gchar *filename, double **matrix_end, int *pointer_width, int *pointer_height 
// return an double array with grey_pixel vals, and the pointers vals
double * file_to_matrix(GdkPixbuf *pixbuf, double **matrix_endint, *pointer_width, int *pointer_height );


#endif

