#include "cutting.h"
#include <stdio.h>
#include "testing_cut.h"
#include "image_to_matrix.h"

void test_cut()
{
printf("test cutting:\n");

double C[] = {1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,0,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	     	  1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
 


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
    double *matrix = file_to_matrix_grey("./image_test/test_cut",0,0,0);
	size_t l = 503;
	size_t h = 640;	
	W_list *word_list = cutting(matrix,l,h,1);
		
	
	while(word_list!=NULL)
	{
		size_t posx = (word_list->info.pos - matrix)/l;
		size_t posy = (word_list->info.pos - matrix)%l;
		if (word_list->info.type == WORD)
    	{
        	for(size_t i = posx-1; i< posx + word_list->info.width +1;++i)
				{
					for(size_t j=posy-1;
							i< posy + word_list->info.height+1;++i)		
					{
						if(is_valid(i,j,l,h))
						{
							*(matrix + i*l + j)= 0.8; 
						}		
					}			
				} 
    	}
		else if (word_list->info.type == SPACE)
		{
			for(size_t i = posx-1; i< posx + word_list->info.width +1;++i)
			{	
				if(is_valid(i,posy,l,h))
				{
					*(matrix+i*l)= 0.6;
				}
			}		
		}
	}	
	
	GtkWidget *new_image = image_from_matrix(matrix,l,h);
}

