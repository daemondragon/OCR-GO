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
					*(matrix + (posy - 1) * l + i) = 0.8;
				}
				if(is_valid(i, posy + hei + 1 , l, h))
			   	{
					*(matrix + (posy + hei + 1) * l + i) = 0.8;
				}
			}

			for(size_t j = posy - 1; j < posy + hei + 1  ; ++j)
			{
				if(is_valid(posx-1, j ,l ,h))
			   	{
					*(matrix + j*l + posx -1)= 0.8;
				}

				if(is_valid(posx + wid, posy + wid + 1 , l, h))
			   	{
					*(matrix + j*l + posx + wid + 1) = 0.8;
				}
			}

    	}
		else if (word_list->info.type == SPACE)
		{
			size_t posx = (word_list->info.pos - matrix)/l;
			size_t posy = (word_list->info.pos - matrix)%l;

			for(size_t i = posx-1; i< posx + word_list->info.width +1;++i)
			{
			    if(is_valid(i,posy,l,h))
				{
					//*(matrix+i*l)= 0.6;
				}
			}
		}
		else
		{//NEW_LINE
		    if (previous && word_list->nxt)
		    {
		        double *pos_up = (previous->info.pos -
		            (previous->info.pos - matrix) % l)
		                + l * previous->info.height;
		        double *pos_down = (word_list->nxt->info.pos -
		            (word_list->nxt->info.pos - matrix) % l);
		        double *middle = (double*)((size_t)pos_up / 2 +
		                                   (size_t)pos_down / 2);
		        for (int i = 0 ; i < l ; ++i)
		        {
		            middle[i] = 0.8;
		        }
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
