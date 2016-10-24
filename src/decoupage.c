#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include "info_word.h"

int decoupage (void){

return 0;
}

char black_line(double *matrix,int l,int seuil) {
	int dots=0;
	double *temp = matrix;	
	for(int i=l;i>0;--i){
		if (*temp){
			dots++;
			if(dots>=seuil){
				return 1
			}
		}
		temp++;
	}
	return 0;
}

double* h_search_white(double *matrix,double *start, int l,int seuil){
	double *end_zone = matrix;
	while(black_line(end_zone,l,seuil)&& end_zone>start+1){
		end_zone-=l;
		}	
 	return end_zone;
} 

double* h_search_black(double *matrix,double *start, int l,int seuil){
        double *end_zone = matrix;
        while(!((black_line(end_zone,l,seuil)))&& end_zone>start+1){
                end_zone-=l;
                } 
        return end_zone;
}

W_list* cutting(double *matrix,int l, int seuil){
	double *cursor= matrix + l - 1;
	double *word_start;
	double *word_end;
	float	word_space=0;
	double *band_start;
	double *band_end;
	W_list *word_list
	while (cursor >= matrix){
		band_start = h_search_black(cursor-(double)l, matrix,l,seuil);
		cursor=band_start;
		band_end = h_search_white(cursor,matrix,l,seuil);
		 
		
		}


