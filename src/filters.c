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
	double * matrix = file_to_matrix_grey(filename, matrix_end,
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

GdkPixbuf *extract_image(GdkPixbuf *input_pixbuf, int x, int y, int w, int h)
{
    guchar  *input_pixels     = gdk_pixbuf_get_pixels(input_pixbuf);
    gint    input_channel     = gdk_pixbuf_get_n_channels(input_pixbuf);
    gint    input_width       = gdk_pixbuf_get_width(input_pixbuf);
    gint    input_height      = gdk_pixbuf_get_height(input_pixbuf);
    gint    input_rowstride   = gdk_pixbuf_get_rowstride(input_pixbuf);

    if (x >= input_width || y >= input_height)
        return (NULL);

    if (x < 0)
    {
        w += x;
        x = 0;
    }
    if (y < 0)
    {
        h += y;
        y = 0;
    }
    if (x + w >= input_width)
        w = input_width - x;
    if (y + h >= input_height)
        h = input_height - y;
    
    GdkPixbuf *output_pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, 0, 8, w, h);
    if (output_pixbuf)
        return (NULL);

    guchar  *output_pixels     = gdk_pixbuf_get_pixels(input_pixbuf);
    gint    output_channel     = gdk_pixbuf_get_n_channels(input_pixbuf);
    gint    output_rowstride   = gdk_pixbuf_get_rowstride(input_pixbuf);

    for (gint j = 0; j < h; ++j)
    {
        for (gint i = 0; i < w; ++i)
        {
            output_pixels[(i * output_channel) + (j * output_rowstride)] =
                input_pixels[((i + x) * input_channel) +
                          ((j + y) * input_rowstride)];
            output_pixels[(i * output_channel) + (j * output_rowstride) + 1] =
                input_pixels[((i + x) * input_channel) +
                          ((j + y) * input_rowstride) + 1];
            output_pixels[(i * output_channel) + (j * output_rowstride) + 2] =
                input_pixels[((i + x) * input_channel) +
                          ((j + y) * input_rowstride) + 2];
        }
    }

    return (output_pixbuf);
}

void erase_zone_from_image(GdkPixbuf *pixbuf, int x, int y, int w, int h)
{
    guchar  *pixels     = gdk_pixbuf_get_pixels(pixbuf);
    gint    channel     = gdk_pixbuf_get_n_channels(pixbuf);
    gint    width       = gdk_pixbuf_get_width(pixbuf);
    gint    height      = gdk_pixbuf_get_height(pixbuf);
    gint    rowstride   = gdk_pixbuf_get_rowstride(pixbuf);

    if (x >= width || y >= height)
        return;

    if (x < 0)
    {
        w += x;
        x = 0;
    }
    if (y < 0)
    {
        h += y;
        y = 0;
    }
    if (x + w >= width)
        w = width - x;
    if (y + h >= height)
        h = height - y;

    for (gint j = 0; j < h; ++j)
    {
        for (gint i = 0; i < w; ++i)
        {
            pixels[(i * channel) + (j * rowstride)]     = 255;
            pixels[(i * channel) + (j * rowstride) + 1] = 255;
            pixels[(i * channel) + (j * rowstride) + 2] = 255;
        }
    }
}

void launch_bin()
{
	GtkWidget *image = file_to_image_bin("image_test/binarize.png");
    GtkWidget *Window;
    Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(Window),5);
    gtk_window_set_default_size(GTK_WINDOW(Window),600,600);
    gtk_window_set_title(GTK_WINDOW(Window),"OCR TEST IMAGE BIN");
    g_signal_connect(G_OBJECT(Window),"destroy",
                     G_CALLBACK(gtk_main_quit),NULL);
    gtk_container_add(GTK_CONTAINER(Window),GTK_WIDGET(image));
    gtk_widget_show_all(Window);
}
void test_filters ()
{
	//GtkWidget *test = file_to_image_bin("image_test/binarize.png");


	int argc = 0;
	char **argv = NULL;
	gtk_init(&argc, &argv);
	GtkWidget *image = gtk_image_new_from_file ("image_test/binarize.png");
    GtkWidget *Window;
	GtkWidget *Button;
	GtkWidget *table;
	GtkWidget * Box;
	Button = gtk_button_new_with_label("Binarize");
    Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(Window),5);
    gtk_window_set_default_size(GTK_WINDOW(Window),600,600);
    gtk_window_set_title(GTK_WINDOW(Window),"OCR TEST IMAGE");
    g_signal_connect(G_OBJECT(Window),"destroy",
                     G_CALLBACK(gtk_main_quit),NULL);
    Box = gtk_vbox_new(FALSE,0);


	table = gtk_table_new(10,10,TRUE);
	gtk_container_add(GTK_CONTAINER(Window),GTK_WIDGET(table));

	gtk_box_pack_start(GTK_BOX(Box),image,FALSE,FALSE,5);
	gtk_table_attach(GTK_TABLE(table),
	                   Button,9,10,5,7,GTK_EXPAND | GTK_FILL, GTK_EXPAND,0,0);
	gtk_table_attach_defaults(GTK_TABLE(table),Box,0,8,0,8);
  	g_signal_connect(G_OBJECT(Button),"clicked",G_CALLBACK(launch_bin),NULL);
    gtk_widget_show_all(Window);
    gtk_main();
}
