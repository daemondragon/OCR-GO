#include <err.h>
#include <stdlib.h>

#include "info_word.h"

W_list* WL_init(void){
	W_list *new_list = malloc (sizeof(W_list));
	new_list->size = 0;
	new_list->infos = NULL;
	return new_list;
}
void  WL_add(W_list *liste ,infos to_add)
{
	
	new_word = malloc (sizeof(infos));
	
	new_word->type = to_add.type;
	new_word->pos = to_add.pos ;
	new_word->width = to_add.width;
	new_word->height = to_add.height;

	new_word->nxt = liste->first;
	liste->first = new_word;
	liste->size ++ ;
}

infos WL(W_list *liste ,int i)
{
	for(int j=0;j<i;++j){
		liste=liste->nxt;
	}
	return liste->info;
}

void WL_free(W_list *list)
{
    if (!list->size )
        {
		free(list);
		return;
	}
	infos *actual = list->first;
	while(actual != NULL)
	{
	    infos *temp = actual->nxt;
	    free(actual);
	    actual = temp;
	}
	free(list);
}

void : WL_clean(W_list *list, float min, float height_rate)
{
    if (!list->size)
        return NULL;

    infos *actual = list->first;
    
    while (actual)
    {
        if (actual->type == SPACE)
        {
            if (actual->width <= min + height_rate * actual->height) 
            {
                infos *temp = actual->nxt;
                free(actual);
		actual = temp;
            }
            else
                actual = actual->nxt;
        }
        else
            actual = actual->nxt;
    }

}
