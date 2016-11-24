#ifndef IMAGE_TO_MATRIX_H
#define IMAGE_TO_MATRIX_H

#include "image_to_matrix.h"
#include <gtk/gtk.h>

// input GdkPixbuf *pixbuf, double **matrix_end,
// int *pointer_width, int *pointer_height
// return an double array with grey_pixel vals , and the pointers vals
double *pixbuf_to_matrix_grey(GdkPixbuf *pixbuf, double **matrix_end,
			int *pointer_width, int *pointer_height);

// input file path const gchar *filename, double **matrix_end,
// int *pointer_width, int *pointer_height
// return an double array with grey_pixel vals, and the pointers vals
double *file_to_matrix_grey(const char *filename, double **matrix_end,
			int *pointer_width, int *pointer_height );

// create image from matrix
GtkWidget * image_from_matrix (double *matrix, int width, int height);

// copy a matrix
double *new_matrix_copy(double *matrix, double *matrix_end,
			double **new_matrix_end);

//scale a matrix
//double *matrix_pos is the start position of the scaled zone
//int line is the size of the line in the the matrix given by matrix_pos
//int matrix_width and int matrix_height are the zone of matrix_pos which are
//going to be scaled
//int width and int height are the dimensions of the returned matrix
double *matrix_scale (double *matrix_pos, int line, int matrix_width, int
		        matrix_height, int width, int height);


void test_mat_copy();

#endif

