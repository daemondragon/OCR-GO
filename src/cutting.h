#ifndef CUTTING_H
#define CUTTING_H

#include "info_word.h"

char is_black_line(double *start, int weight, int threshold);
char is_black_column(double *start, double *end, int weigth, int threshold);

void v_cutting(double *band_start,
		double *band_end,
		int l,
		W_list *word_list,
		float *word_space,	
		float *word_count);

W_list* cutting(double *matrix, size_t weight, size_t height, int threshold);

#endif
