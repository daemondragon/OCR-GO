#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

double * pixbuf_to_matrix_grey(GdkPixbuf *pixbuf,double **matrix_end, int *pointer_width, int *pointer_height)
{
	guchar *pixel=NULL;
	gint channel=0;
	gint width=0;
	if (!pixbuf)
	{
		perror("Erreur fonction pixbuf_to_matrix_grey no pixbuf");
		return NULL;
	}
	pixel=gdk_pixbuf_get_pixels(pixbuf);
	channel=gdk_pixbuf_get_n_channels(pixbuf);
	width=gdk_pixbuf_get_width(pixbuf);
	gint height = gdk_pixbuf_get_height(pixbuf);
	*pointer_width = width;
	*pointer_height = height;
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

double * file_to_matrix_grey(const char *filename, double **matrix_end, int *pointer_width, int *pointer_height)
{	
	GError *error = NULL;
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	return pixbuf_to_matrix_grey(pixbuf, matrix_end, pointer_width, pointer_height);
}

GtkWidget * image_from_matrix (double *matrix, int width, int height)
{
	GdkPixbuf *pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, 0, 8, width, height);
	guchar *pixel=gdk_pixbuf_get_pixels(pixbuf);
	int channel=gdk_pixbuf_get_n_channels(pixbuf);
	for (gint y = 0; y<height; y++)
        {
                for (gint x = 0; x<width; x++)
                {
			int grey_level = *(matrix + x + y*width)*255;
                        pixel[(x*channel)+(y*width*channel)] = grey_level;
                        pixel[(x*channel)+(y*width*channel)+1] = grey_level;
                        pixel[(x*channel)+(y*width*channel)+2] = grey_level ;
                }
        }
        return gtk_image_new_from_pixbuf(pixbuf);

}


/*double * image_to_matrix_colors(GdkPixbuf *pixbuf) 	//not used and not tested
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
}*/
/*
static void activate (GtkApplication* app, gpointer user_data)
{
	double * matrix_end;
	int width, height;
	double  *matrix = file_to_matrix_grey("test", &matrix_end, &width, &height);
	binarize_simple(matrix, matrix_end);
	GtkWidget *Image = image_from_matrix(matrix, width ,height);
	GtkWidget *window;

	window = gtk_application_window_new (app);
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);
	gtk_container_add(GTK_CONTAINER (window), Image);
	gtk_widget_show_all (window);
}


int main(int argc, char *argv[])	//test the image_to_matrix_grey
{
	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
*/
