#ifndef INFO_WORD_H
#define INFO_WORD_H


#include <stdlib.h>

typedef

typedef struct infos
{
	enum type{WORD, SPACE, NEW_LINE}type;
	double *pos;
	size_t width;
	size_t height;
	struct infos *nxt;
}infos;

typedef struct W_list
{
	size_t size;
	struct infos *first;
}W_list;

// renvoi une liste null
W_list* WL_init(void);

// ajoute en tete de liste
void  WL_add(W_list *liste ,infos toadd);

// retourn l info a la ieme position de la liste
infos WL(W_list *liste ,int i);

// libere la liste
void WL_free(W_list *liste);


// delete spaces between the letter of a single word
void  WL_clean(W_list *liste, float min, float height_rate);

#endif
