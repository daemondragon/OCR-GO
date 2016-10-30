#include <stdio.h>
#include <stdlib.h>
#include "image_to_matrix.h"

void binarize_simple(double *matrix, double *end_matrix)
{
	double mean = 0;
        for (double *index = matrix; index < end_matrix; index++)
	{
		mean += *index;
	}
	mean = mean / (end_matrix - matrix);
	for (double *index = matrix; index < end_matrix; index++)
	{
		if (*index > mean)
		{
			*index = 1.0;
		}
		else
		{
			*index = 0.0;
		}
	}

}

void _binarize_mean_zone(double *matrix,int xmin, int xmax,
			int ymin, int ymax, int width)
{
	//xmin xmax ymin ymax set to limit the zone
	double mean = 0;
	for (int y = ymin; y < ymax; y++)
	{
		for (int x = xmin; x < xmax; x++)
		{
			mean += *(matrix + x + y*width);
		}
	}
	mean = mean / ((xmax-xmin)*(ymax-ymin));
	for (int y = ymin; y < ymax; y++)
	{
		for (int x = xmin; x < xmax; x++)
		{
			if (*(matrix + x + y*width) > mean)
			{
				*(matrix + x + y*width) = 1.0;
			}
			else
			{
				*(matrix + x + y*width) = 0.0;
			}
		}
	}

}
void binarize_mean_zone(double *matrix, int width, int height, int nb_zone)
{
	//create nb_zone^2 2 zones
	int xmin = 0,xmax, ymin = 0, ymax = height/nb_zone;
	while (ymin<height)
	{
		xmin = 0;
		xmax= width/nb_zone;
		if (ymax>height)
		{
			ymax = height;
		}
		while (xmin<width)
		{
			if (xmax>width)
			{
				xmax = width;
			}
			_binarize_mean_zone(matrix, xmin, xmax, ymin, ymax, width);
			xmin = xmax;
			xmax += width/nb_zone;
		}
		ymin = ymax;
		ymax += height/nb_zone;
	}
}

double *file_to_matrix_bin(const char *filename, double **matrix_end,
		                        int *pointer_width, int *pointer_height )
{
	double * matrix = file_to_matrix_bin(filename, matrix_end,
			     		pointer_width, pointer_height );
	binarize_simple(matrix, *matrix_end);
	return matrix;
}

GtkWidget * file_to_image_bin(const char *filename)
{
	int width, height;
	double *matrix_end;
	double *matrix = file_to_matrix_bin(filename, &matrix_end,
					&width, &height);
	return image_from_matrix(matrix, width, height);
}
void test_filters ()
{
	file_to_image_bin("test");
}
