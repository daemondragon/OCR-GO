#ifndef CUTTING_H
#define CUTTING_H

#include "info_word.h"

char is_black_line(double *start, int width, int threshold);
char is_black_column(double *start, double *end, int width, int threshold);

W_list * v_cutting(double *band_start, double *band_end, int width,
                   W_list *word_list,
                   int *sum_space_size, int *space_count);

W_list* cutting(double *matrix, size_t width, size_t height, int threshold);

#endif
