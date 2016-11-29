#ifndef FILTERS_H
#define FILTERS_H

#include "filters.h"
// This function binarize the matrix given as argument
void binarize_simple(double *matrix, double *end_matrix);

void launch_bin();
void test_filters();

double *file_to_matrix_bin(const char *filename, double **matrix_end,
		     	int *pointer_width, int *pointer_height );

GtkWidget *file_to_image_bin(const char *filename);

//Extract a w * h picture from image, starting at (x;y)
GtkWidget *extract_image(GtkWidget *image,
                         int x, int y, int w, int h);


#endif

