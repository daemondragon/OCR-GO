#include <err.h>
#include <stdlib.h>

#include "info_word.h"

W_list* WL_init(void){
	return NULL;
}
W_list*  WL_add(W_list *liste ,infos to_add)
{
	W_list *new_word;
	new_word = malloc (sizeof(W_list));
	new_word->info = to_add;
	new_word->nxt = liste;
	return new_word;
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
    if (!list)
        return;

	while(list->nxt != NULL)
	{
	    W_list *temp = list->nxt;
	    free(temp);
	    list->nxt = list->nxt->nxt;
	}
	free(list);
}

W_list* WL_nxt(W_list *liste){
	return liste->nxt;
}


W_list* WL_clean(W_list *list, float min)
{
    if (!list)
        return (NULL);

    W_list *actual = list;
    //First element must be a WORD
    while (actual->nxt)
    {
        if (actual->nxt->info.type == SPACE)
        {
            if (actual->nxt->info.width <= min)
            {
                W_list *temp = actual->nxt;
                actual->nxt = actual->nxt->nxt;
                free(temp);
            }
            else
                actual = actual->nxt;
        }
        else
            actual = actual->nxt;
    }

	return list;
}
