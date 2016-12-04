#ifndef IMG2TXT_H
#define IMG2TXT_H


#include <stdlib.h>
#include <stdio.h>

#include "feed_forward.h"
#include "image_to_matrix.h"
#include "cutting.h"


// prend en parametre l'image sous la forme de son chemin ainsi que ses différent paramètre
// par defaut on donnera 1 pour le threshold et 0.1 pour le height_rate
// le neural network doit etre créer au préalable
char* img_to_string(double *matrix, size_t width , size_t height, int threshold, float height_rate,neural_network_t *net);


//sauvegarde la string dans un fichier a coté de l'image
// attention l'extension du fichier doit etre en 3 lettres ou plus
// le nom du fichier ne peut pas comporter de "." ailleur que au debut
// ou avant l'extention. l'extension doit etre présente dans le nom du fichier
void string_to_file(char *filename, char *string);


#endif
