#ifndef LOAD_EXEMPLES_H
#define LOAD_EXEMPLES_H

#include "learning.h"

neural_exemple_t* load_exemples(char directory_name[],
                                double* (*load_picture)(char*),
                                uint32_t *nb_exemples_loaded);

#endif
