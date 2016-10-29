#include <err.h>
#include <stdlib.h>
#include <stdio.h>

#include "cutting.h"

#define VERTICAL_PERCENTAGE_THRESHOLD   0.1

char is_black_line(double *start, int weight, int threshold)
{
	int dots = 0;
    double *actual = start;

    for(int i = 0; i < weight; ++i, ++actual)
	{
		if (*actual < 0.10)//Black
		{
			dots++;
		}
	}

	return (dots >= threshold);
}

char is_black_column(double *start, double *end, int weigth, int threshold)
{
    int dots = 0;
    double *actual = start;

    while (actual <= end)
    {
        if (*actual < 0.1)//Black
        {
            dots++;
        }
        actual += weight;
    }

    return (dots >= threshold);
}


//return the new modified list (else it will be lost)
W_list * v_cutting(double *band_start, double *band_end, int weight,
                   W_list *word_list,
                   float *sum_space_size, float *space_count)
{
    int threshold = ((band_end - band_start) * VERTICAL_PERCENTAGE_THRESHOLD
                    / weight);
    double *char_start = NULL;
    double *char_end = NULL;
    /*
    int i = 0;
    while (i < weight &&
           !is_black_column(band_start + i, band_end + i, weight, threshold))
        ++i;

    while (i < weight)
    {
        ++(*space_count);//It's done wrongfully the first time we encounter
        //a white space
        while (i < weight &&
           !is_black_column(band_start + i, band_end + i, weight, threshold))
        {
            ++(*sum_space_size);
            ++i;
        }
        while (i)
    }
    */
    return (word_list);

	double h = ((band_end-band_start)+1)/l -1;
	infos new_word;
	for(int k=0 ; k<l ; ++k)
	{
		
		// white column 
		new_word.width=0;
		while(!(black_column(band_start, band_end-k , l)))
		{
			new_word.width++;
			k++;	
		}
		new_word.type= E;
		new_word.pos = band_end-k - (int)(h*l); 
		new_word.height = h+1;
		WL_add(word_list,new_word );


		// a word
		new_word.width=0;
		while(black_column(band_start,band_end-k,l))
		{
			new_word.width++;
			k++;
		}
		new_word.type= W;
		new_word.pos = band_end-k- (int)(h*l) ;  
		new_word.height = h+1;
		WL_add(word_list,new_word );
		*word_space += new_word.width;
		++*word_count;
	}
	new_word.type = N;
	WL_add(word_list, new_word);
}


W_list* cutting(double *matrix, size_t weight, size_t height, int threshold)
{
    //actual is the first pixel of the last line
    double *actual = matrix + weight * (height - 1);

    int sum_space_size = 0;
    int space_count = 0;
    W_list *word_list = WL_init();

    while (matrix <= actual)
    {
        while (matrix <= actual && !is_black_line(actual, weight, threshold))
            actual -= weight;
        //We are on the last black line of a horizontal block (first pixel)

        double *band_start = actual - weight;
        double *band_end = actual;
        while (matrix <= band_start &&
               is_black_line(band_start, weight, threshold))
            band_start -= weight;

        //We are on the white line just before the first black line (band)
        band_start += weight;

        if (matrix > band_start)
            break;//Nothing found : cursor before matrix start

        //TRAITEMENT
        printf("%d %d\n", (band_start - matrix) / weight, 
                          (band_end - matrix) / weight);

        word_list = v_cutting(band_start, band_end, weight,
                              word_list, sum_space_size, space_count);
        
        actual = band_start - weight;
    }
    /*
	double *cursor= matrix + size - 1;
	float	word_space =0;
	float	word_count =0;
	double *band_start;
	double *band_end;
	
	while(cursor > matrix){
		band_start = h_search_black(matrix,cursor,l,seuil);
		cursor=band_start-l;
		if(cursor>matrix){
		band_end = h_search_white(matrix,cursor+l-1,l,seuil);
		cursor=band_end;
		v_cutting(band_start,band_end,l,word_list,&word_space,&word_count);
		}
	}
	*/
	if (space_count > 0)
	    WL_clean(word_list, sum_space_size / space_count);

	return (word_list);
}

