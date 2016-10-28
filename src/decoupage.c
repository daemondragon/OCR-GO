#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include "info_word.h"

#define VERTICAL_SEUIL 1

char black_line(double *matrix,int l,int seuil)
{
	int dots=0;
	double *temp = matrix;	
	for(int i=l;i>0;--i)
	{
		if (*temp>0.90)
		{
			dots++;
			if(dots>=seuil)
			{
				return 1;
			}
		}
		temp++;
	}
	return 0;
}

double* h_search_white(double *matrix,double *start, int l,int seuil){
	double *end_zone = start;
	while(black_line(end_zone,l,seuil)&& end_zone>matrix+1){
		end_zone-=l;
	}	
	return end_zone;
} 

double* h_search_black(double *matrix,double *start, int l,int seuil){
	double *end_zone = start;
	while(!((black_line(end_zone,l,seuil)))&& end_zone>matrix+1){
		end_zone-=l;
	} 
	return end_zone;
}

char black_column(double *band_start,double *band_end,int l)
{
double *cursor = band_end;
int dot = 0;
int seuil = (int)( ((band_start-band_end)/(float)l) *0.1* VERTICAL_SEUIL + 0.5 ) ;
  for(;cursor>band_start;cursor+=l)
    {
    if(*cursor > 0.9)
      {
      dot++;
      if(dot>= seuil)
	{
	return 1;
	}
      }
    } 
return 0;
}

void v_cutting(double *band_start,
		double *band_end,
		int l,
		W_list *word_list,
		float *word_space,	
		float *word_count )
{

}



W_list* cutting(double *matrix,int size,int l, int seuil){
	double *cursor= matrix + size - 1;
	float	word_space =0;
	float	word_count =0;
	double *band_start;
	double *band_end;
	W_list *word_list=WL_init();
	while(cursor >= matrix){
		band_start = h_search_black(matrix,cursor+l-1,l,seuil);
		cursor=band_start;
		band_end = h_search_white(matrix,cursor+l-1,l,seuil);
		cursor=band_end;
		v_cutting(band_start,band_end,l,word_list,&word_space,&word_count);
	}
	return word_list;
}

