#include <err.h>
#include <stdlib.h>
#include <stdio>

typedef struct infos{
	enum type{'e','c','n'};
	int posx;
	int posy;
	int lar;
	int lon;
}

typedef struct W_list{

	infos info;
	struct W_list *nxt=NULL;

}

*W_list WL_nul(void){
	return NULL;
}

void  WL_add(*W_list liste ,infos toadd){
	*W_list new_word;
	new_word = (*W_list)malloc (sizeof(W_list));
	new_word -> info= toadd;
	while (liste->nxt!=NULL){
		liste=liste->nxt;
	}
	liste -> nxt = new_word; 
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
		liste.free();
		liste=temp;
	}
}









