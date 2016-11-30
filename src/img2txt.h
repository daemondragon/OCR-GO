#ifndef IMG2TXT_H
#define IMG2TXT_H


#include <stdlib.h>
#include <stdio.h>
#include <feed_forward.h>
#include <image_to_matrix.h>
#include <cutting.h>

char* img_to_string(double *matrix, size_t width , size_t height, int threshold, float height_rate,neural_network_t *net);


#endif
