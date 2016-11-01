#include "cutting.h"
#include <stdio.h>
#include "testing_cut.h"
#include "image_to_matrix.h"


char is_valid(size_t x ,size_t y, size_t width, size_t heigth)
{
    return (x < width && y < heigth);
}

void show_cutting()
{
   	int l = 40;
	int h = 20;

    double *matrix = file_to_matrix_grey("./image_test/test_cut.png",0,&l,&h);

    W_list *word_list = cutting(matrix,l,h,1);
    W_list *previous = NULL;

	while(word_list!=NULL)
	{
		//printf( "%d \n" ,word_list->info.type);
		if (word_list->info.type == WORD)
    	{
    	    #ifndef DEBUG
    	    printf("word : w:%d h:%d\n", word_list->info.width,
    	                               word_list->info.height);
    	    #endif

			size_t posx = (word_list->info.pos - matrix) % l;
			size_t posy = (word_list->info.pos - matrix) / l;
			size_t hei = word_list->info.height;
			size_t wid = word_list->info.width;

            #ifndef DEBUG
            printf("pos: %d %d", posx, posy);
            #endif

        	for(size_t i = posx - 1; i < posx + wid + 2; ++i)
		    {
				if(is_valid(i, posy-1, l, h))
			   	{
					*(matrix + (posy - 1) * l + i) = 0.5;
				}
				if(is_valid(i, posy + hei + 1 , l, h))
			   	{
					*(matrix + (posy + hei + 1) * l + i) = 0.5;
				}
			}

			for(size_t j = posy - 1; j < posy + hei + 1  ; ++j)
			{
				if(is_valid(posx-1, j ,l ,h))
			   	{
					*(matrix + j*l + posx -1)= 0.5;
				}

				if(is_valid(posx + wid, posy + wid + 1 , l, h))
			   	{
					*(matrix + j*l + posx + wid + 1) = 0.5;
				}
			}
    	}
		else if (word_list->info.type == SPACE)
		{
            double *pos = word_list->info.pos + l * word_list->info.height;

			for(size_t i = 2; i < word_list->info.width - 2; ++i)
		        pos[i] = 0.5;
		}
		else
		{//NEW_LINE
		    if (previous && word_list->nxt)
		    {
		        size_t pos_up = (previous->info.pos - matrix +
		                         l * previous->info.height) / l * l;
		        size_t pos_down = (word_list->nxt->info.pos - matrix) / l *l;

		        size_t middle = ((pos_up + pos_down) / 2) / l * l;

		        for (int i = 0 ; i < l ; ++i)
		            matrix[middle + i] = 0.5;
		    }
		}
		previous = word_list;
		word_list = WL_nxt(word_list);
	}

	GtkWidget *new_image = image_from_matrix(matrix,l,h);
 	test_window(new_image);
}

void test_window(GtkWidget *widget)
{
    int argc = 0;
    char **argv = NULL;
    gtk_init(&argc, &argv);

    GtkWidget *Window;
    GtkWidget *Box;

    Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(Window),5);
    gtk_window_set_default_size(GTK_WINDOW(Window),600,600);
    gtk_window_set_title(GTK_WINDOW(Window),"OCR TEST IMAGE");
    g_signal_connect(G_OBJECT(Window),"destroy",
                                             G_CALLBACK(gtk_main_quit), NULL);
    Box = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(Window), Box);

    gtk_box_pack_start(GTK_BOX(Box), widget,FALSE,FALSE,5);
    gtk_widget_show_all(Window);
    gtk_main();
}
