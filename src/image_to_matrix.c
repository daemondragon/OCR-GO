#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>

double * image_to_matrix_grey(GdkPixbuf *pixbuf,double **matrix_end)
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
	double *matrix = malloc(sizeof(double) * width * height);
	for (gint y = 0; y<height; y++)
	{
		for (gint x = 0; x<width; x++)
		{
			red   = pixel[(x*channel)+(y*width*channel)];
			green = pixel[(x*channel)+(y*width*channel)+1];
			blue  = pixel[(x*channel)+(y*width*channel)+2];
			*(matrix + x + y*width) = (red+green+blue); 
			*(matrix + x + y*width) = *(matrix + x + y*width)/765;//considering that the max value of each colors is 255
		}
	}
	*matrix_end = matrix + width*height;
	return matrix;
}
double * image_to_matrix_colors(GdkPixbuf *pixbuf)
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
				*(matrix + x * 3 + y * width * 3)  = pixel[(x*channel)+(y*width*channel)]/255;
				*(matrix + x * 3 + y * width * 3 + 1) = pixel[(x*channel)+(y*width*channel)+1]/255;
				*(matrix + x * 3 + y * width * 3 + 2) = pixel[(x*channel)+(y*width*channel)+2]/255;	
		}
	}
	return matrix;
}

/*int main(int argc, char *argv[])	//test the image_to_matrix_grey
{
	double * matrix_end;
	GError *error = NULL;
	GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file("test.png",&error);	
	double  *matrix = image_to_matrix_grey(pixbuf, &matrix_end);
	printf("I am here\n");
	for (double *index = matrix; index<matrix_end; index++)
 	{
		printf("%f\n",*index);
	}
	return 0;
}*/
