#include <err.h>
#include <stdlib.h>
#include <stdio.h>

#include "cutting.h"

#define VERTICAL_PERCENTAGE_THRESHOLD   0.1

char is_black_line(double *start, int width, int threshold)
{
	int dots = 0;
    double *actual = start;

    for(int i = 0; i < width; ++i, ++actual)
	{
		if (*actual < 0.10)//Black
		{	
			dots++;
		}
	}

	return (dots >= threshold);
}

char is_black_column(double *start, double *end, int width, int threshold)
{
    int dots = 0;
    double *actual = start;

    while (actual <= end)
    {
        if (*actual < 0.1)//Black
        {
            dots++;
        }
        actual += width;
    }

    return (dots >= threshold);
}


//return the new modified list (else it will be lost)
W_list * v_cutting(double *band_start, double *band_end, int width,
                   W_list *word_list,
                   int *sum_space_size, int *space_count)
{
    int threshold = ((band_end - band_start) * VERTICAL_PERCENTAGE_THRESHOLD
                    / width);
    threshold = (threshold <= 1 ? 1 : threshold);

    int temp_sum_space_size = 0;
    int temp_space_count = 0;
    
    infos info;
    info.height = (band_end - band_start) / width + 1;

    //Add return to list
    info.type = NEW_LINE;
    info.pos = NULL;//ONLY position in list is important
    info.width = 0;
    word_list = WL_add(word_list, info);

    int i = width - 1;
    while (i >= 0 &&
           !is_black_column(band_start + i, band_end + i, width, threshold))
        --i;

    while (i >= 0)
    {
        (*sum_space_size) += temp_sum_space_size;
        (*space_count) += temp_space_count;
        temp_sum_space_size = 0;
        temp_space_count = 0;

        double *char_end = band_start + i;
        while (i >= 0 && is_black_column(band_start + i,
                                         band_end + i,
                                         width,
                                         threshold))
        {
            --i;
        }
        double *char_start = band_start + i + 1;
        //End of char

        //Add char
        info.type = WORD;
        info.pos = char_start;
        info.width = (char_end - char_start);
        word_list = WL_add(word_list, info);

        //Space
        ++temp_space_count;
        while (i >= 0 && !is_black_column(band_start + i,
                                          band_end + i,
                                          width,
                                          threshold))
        {
            --i;
            ++temp_sum_space_size;
        }

        //End of white columns
        if (i >= 0)
        {//add space
            info.type = SPACE;
            info.pos = char_end;
            info.width = (char_end - (band_start + i + 1));
            word_list = WL_add(word_list, info);
        }
    }

    return (word_list);
}


W_list* cutting(double *matrix, size_t width, size_t height, int threshold)
{
    //actual is the first pixel of the last line
    double *actual = matrix + width * (height - 1);

    int sum_space_size = 0;
    int space_count = 0;
    W_list *word_list = WL_init();

    while (matrix <= actual)
    {
        while (matrix <= actual && !is_black_line(actual, width, threshold))
            actual -= width;

        //We are on the last black line of a horizontal block (first pixel)

        double *band_start = actual - width;
        double *band_end = actual;
        while (matrix <= band_start &&
               is_black_line(band_start, width, threshold))
            band_start -= width;

        //We are on the white line just before the first black line (band)
        band_start += width;

        if (matrix > band_start)
            break;//Nothing found : cursor before matrix start

        //WORK ON BAND
        #ifndef DEBUG
        printf("lines found! %d %d\n", (band_start - matrix) / width,
                                       (band_end - matrix) / width);
        #endif
        
        word_list = v_cutting(band_start, band_end, width,
                              word_list, &sum_space_size, &space_count);
        
        actual = band_start - width;
    }

	if (space_count > 0)
	    word_list = WL_clean(word_list, sum_space_size / space_count);

	return (word_list);
}

