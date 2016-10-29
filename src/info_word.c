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

infos WL(W_list *liste ,int i){
	for(int j=0;j<i;++j){
		liste=liste->nxt;
	}
	return liste->info;
}

void WL_free(W_list *liste){
	W_list *temp = liste;
	while(liste->nxt != NULL){
		temp = temp->nxt;
		free(liste);
		liste=temp;
	}
	free(liste);
}

W_list* WL_nxt(W_list *liste){
	return liste->nxt;
}


W_list* WL_clean(W_list *liste, float min)
{
	if(liste==NULL)
	{return NULL;}
	W_list *new_list = liste->nxt;
	free(liste);	
	while(new_list->nxt != NULL)
	{
		if((float)new_list->info.width <=min )
		{	
			W_list *temp  = new_list->nxt;
			free(new_list);
			new_list=temp;
		}
		else
		{
			new_list = new_list->nxt;
		}
	}
	return new_list;
}	
