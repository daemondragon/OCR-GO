#ifndef INFO_WORD_H
#define INFO_WORD_H


#include <stdlib.h>
typedef struct infos
{
	enum type{WORD, SPACE, NEW_LINE}type;
	double *pos;
	size_t width;
	size_t height;
}infos;

typedef struct W_list
{
	infos info;
	struct W_list *nxt;
}W_list;

// renvoi une liste null
W_list* WL_init(void);

// ajoute en tete de liste
W_list*  WL_add(W_list *liste ,infos toadd);

// retourn l info a la ieme position de la liste
infos WL(W_list *liste ,int i);

// libere la liste(ou pas , va savoir)
void WL_free(W_list *liste);

// retourne le prochain element
W_list* WL_nxt(W_list *liste);

W_list* WL_clean(W_list *liste, float min);

#endif
