#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

double * pixbuf_to_matrix_grey(GdkPixbuf *pixbuf,double **matrix_end,
		int *pointer_width, int *pointer_height)
{
	if (!pixbuf)
	{
		perror("Erreur fonction pixbuf_to_matrix_grey no pixbuf");
		return NULL;
	}

	guchar *pixel = gdk_pixbuf_get_pixels(pixbuf);
	gint channel = gdk_pixbuf_get_n_channels(pixbuf);

	gint width = gdk_pixbuf_get_width(pixbuf);
	gint height = gdk_pixbuf_get_height(pixbuf);
	gint rowstride = gdk_pixbuf_get_rowstride(pixbuf);
	
	*pointer_width = width;
	*pointer_height = height;
	guchar red, green, blue;
	double *matrix = malloc(sizeof(double) * width * height);

	for (gint y = 0; y < height; y++)
	{
		for (gint x = 0; x < width; x++)
		{
			red   = pixel[(x * channel)+(y * rowstride)];
			green = pixel[(x * channel)+(y * rowstride) + 1];
			blue  = pixel[(x * channel)+(y * rowstride) + 2];

			matrix[x + y * width] = ((int)red + (int)green + (int)blue) / 765.0;
			//considering that the max value of each colors is 255
		}
	}

    if (matrix_end)
	    *matrix_end = matrix + width * height - 1;

	return matrix;
}

double *file_to_matrix_grey(const char *filename, double **matrix_end,
		int *pointer_width, int *pointer_height)
{
	GError *error = NULL;
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, &error);

	return pixbuf_to_matrix_grey(pixbuf, matrix_end, pointer_width,
			pointer_height);
}

GtkWidget * image_from_matrix (double *matrix, int width, int height)
{
	GdkPixbuf *pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, 0, 8, width, height);
	guchar *pixel=gdk_pixbuf_get_pixels(pixbuf);

	int channel=gdk_pixbuf_get_n_channels(pixbuf);
	gint rowstride = gdk_pixbuf_get_rowstride(pixbuf);

	for (gint y = 0; y < height; y++)
    {
        for (gint x = 0; x < width; x++)
        {
	        int grey_level = matrix[x + y * width] * 255;
            pixel[(x * channel)+(y * rowstride)] = grey_level;
            pixel[(x * channel)+(y * rowstride) + 1] = grey_level;
            pixel[(x * channel)+(y * rowstride) + 2] = grey_level ;
        }
    }

    return gtk_image_new_from_pixbuf(pixbuf);
}


double * new_matrix_copy(double *matrix, double *matrix_end,
		double **new_matrix_end)
{
	size_t len = matrix_end - matrix;
	double *new_matrix = malloc(sizeof(double)*len);
	*new_matrix_end = new_matrix + len;
	for (size_t i = 0; i<len; i++)
	{
		*(new_matrix + i) = *(matrix + i);
	}
	return new_matrix;
}
//not used and not tested
/*double * image_to_matrix_colors(GdkPixbuf *pixbuf)
{
  guchar *pixel=NULL;
  gint channel=0;
  gint width=0;
  if (!pixbuf) return FALSE;
  pixel=gdk_pixbuf_get_pixels(pixbuf);
  channel=gdk_pixbuf_get_n_channels(pixbuf);
  width=gdk_pixbuf_get_width(pixbuf);
  gint height = gdk_pixbuf_get_height(pixbuf);
  guchar red, green, blue;
  double *matrix = malloc(sizeof(double) * width * height * 3);
  for (gint y = 0; y<height; y++)
  {
  for (gint x = 0; x<width; x++)
  {
 (matrix + x*3 + y*width*3)  = pixel[(x*channel)+(y*width*channel)]/255;
 (matrix + x*3 + y*width*3 + 1) = pixel[(x*channel)+(y*width*channel)+1]/255;
 (matrix + x*3 + y*width*3 + 2) = pixel[(x*channel)+(y*width*channel)+2]/255;
 }
 }
 return matrix;
 }*/

void test_mat_copy()
{
	int width=0,height=0;
	double *matrix_end;
	double *matrix = file_to_matrix_grey("test", &matrix_end, &width, &height);
	double *new_matrix_end;
	double * new_matrix = new_matrix_copy(matrix, matrix_end, &new_matrix_end);
	size_t len = matrix_end - matrix, i = 0;
	while (i<len &&  *(matrix + i) == *(new_matrix + i))
	{
		printf("%f = %f\n",*(matrix + i), *(new_matrix + i));
		i++;
	}
	if (i==len)
	{
		printf("matrix sucefully copied\n");
	}
}

