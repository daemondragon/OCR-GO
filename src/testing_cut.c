#include "cutting.h"
#include <stdio.h>
#include "testing_cut.h"
#include "image_to_matrix.h"

double C[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

void test_cut()
{
printf("test cutting:\n");

W_list *word_list = cutting(C, 40, 20, 1);

W_list *temp = word_list;//LES FREE BORDELS !

while(word_list!=NULL)
{
    if (word_list->info.type == WORD)
    {
        printf("WORD(x:%d;y:%d;w:%d;h:%d)\t", (word_list->info.pos - C) % 40,
                                              (word_list->info.pos - C) / 40,
                                              word_list->info.width,
                                              word_list->info.height);
    }
    else if (word_list->info.type == SPACE)
    {
        printf("space(%d)\t", word_list->info.width);
    }
    else
    {
        printf("\nnew_line\n");
    }
    word_list = WL_nxt(word_list);
}

WL_free(word_list);

}

char is_valid(size_t x ,size_t y, size_t width, size_t heigth)
{
return x<width && y<heigth ;
}

void show_cutting()
{
   	int l = 40;
	int h = 20;

    double *matrix = file_to_matrix_grey("./image_test/test_cut.png",0,&l,&h);
	W_list *word_list = cutting(matrix,l,h,1);

	while(word_list!=NULL)
	{
		//printf( "%d \n" ,word_list->info.type);
		if (word_list->info.type == WORD)
    	{
    	    printf("word : w:%d h:%d\n", word_list->info.width,
    	                               word_list->info.height);

			size_t posx = (word_list->info.pos - matrix) % l;
			size_t posy = (word_list->info.pos - matrix) / l;

            printf("pos: %d %d", posx, posy);

        	for(size_t i = posx - 5; i < posx + word_list->info.width + 5;++i)
		    {
				for(size_t j = posy - 5; j < posy + word_list->info.height + 5 ; ++j)		
				{
					if(is_valid(i,j,l,h))
			    	{
						*(matrix + j*l + i)= 0.8; 
					}		
				}			
			}
    	}
		if (word_list->info.type == SPACE)
		{/*
			size_t posx = (word_list->info.pos - matrix)/l;
			size_t posy = (word_list->info.pos - matrix)%l;
			for(size_t i = posx-1; i< posx + word_list->info.width +1;++i)
			{	
				if(is_valid(i,posy,l,h))
				{
					*(matrix+i*l)= 0.6;
				}
			}*/		
		}
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
    g_signal_connect(G_OBJECT(Window),"destroy", G_CALLBACK(gtk_main_quit), NULL);
    Box = gtk_vbox_new(FALSE,0);
    gtk_container_add(GTK_CONTAINER(Window), Box);
    
    gtk_box_pack_start(GTK_BOX(Box), widget,FALSE,FALSE,5);
    gtk_widget_show_all(Window);
    gtk_main();
}
