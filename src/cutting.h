#ifndef CUTTING_H
#define CUTTING_H

#include "info_word.h"

// return 1 if the line is black
// input : start of the line , width of the matrix , treshold to define when a
// line is black
char is_black_line(double *start, int width, int threshold);

// return 1 if the column is black
// input : start of band , end of the band, width of the matrix , treshold to
//define when a column is black
char is_black_column(double *start, double *end, int width, int threshold);

// do the vertical cutting filling the list of words and count the number of
//word/char and their width
W_list * v_cutting(double *band_start, double *band_end, int width,
                   W_list *word_list,
                   int *sum_space_size, int *space_count);

// call the orevious function and return the list of words cleaned
W_list* cutting(double *matrix, size_t width, size_t height, int threshold);

#endif
