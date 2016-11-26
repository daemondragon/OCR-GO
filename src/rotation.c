#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#define PI 3.14159265
#include "image_to_matrix.h"
#include "filters.h"

double *rotate (double *matrix, int *width, int *height, double angle)
{
	double deg_to_rad= PI/180;
	double c = cos(angle*deg_to_rad), s = sin(angle * deg_to_rad);
	int rwidth, rheight, x2, y2, tx, ty; //t are the translations of matrix;
	rwidth =  *width*c + *height*s;
	rheight = *height*c + *width*s;
	tx = (*width*c + *height*s);
	ty = ( *width*s);
	double *rmatrix = malloc(sizeof(double)*rwidth*rheight);
	for (int y = 0; y<*height; y++)
	{
		for (int x = 0; x<*width; x++)
		{
			x2 = (int) (x*c + y*s);
			y2 = (int) (-x*s + y*c + ty);
			if (x2<rwidth && x2>=0 && y2<rheight && y2>=0)
			{
				*(rmatrix + x2 + y2*rwidth) = *(matrix + x + y * *width);
			}
		}
	}
	*width = rwidth;
	*height = rheight;
	return rmatrix;
}
void launch_bin_rotation()
{
    int width, height;
    double *matrix_end;
    double *matrix = file_to_matrix_grey("image_test/binarize.png", &matrix_end,
                    &width, &height);
	binarize_simple(matrix, matrix_end);
	double *matrix2 = rotate(matrix, &width, &height, 10.f);
    GtkWidget *image = image_from_matrix(matrix2, width, height);
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
void test_rotation()
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
    g_signal_connect(G_OBJECT(Button),"clicked",G_CALLBACK(launch_bin_rotation),NULL);
    gtk_widget_show_all(Window);
    gtk_main();
}
