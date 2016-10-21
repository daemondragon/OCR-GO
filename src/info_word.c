#include <err.h>
#include <stdlib.h>


W_list WL_init(void){
	return NULL;
}
W_list  WL_add(*W_list liste ,infos toadd){
	*W_list new_word;
	new_word = (*W_list)malloc (sizeof(W_list));
	new_word -> info= toadd;
	new_word -> nxt = liste; 
}

infos WL(W_list liste ,int i){
	for(int j=0;j<i;++j){
		liste=liste->nxt;
	}
	return liste->info;
}

void WL_free(W_list liste){
	W_list *temp= liste;
	while(temp->nxt!=NULL){
		temp= temp->nxt;
		free(liste);
		liste=temp;
	}
	free(temp);
}

W_list WL_nxt(W_list liste){
	return liste->nxt;
}







