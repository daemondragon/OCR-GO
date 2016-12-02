#include <stdio.h>
#include <stdlib.h>
#include "img2txt.h"
#include <string.h>

char* img_to_string(double *matrix, size_t width , size_t height, int threshold, float height_rate,neural_network_t *net)
{
	W_list *word_list = cutting(matrix, width, height, threshold, height_rate);
	char *string = malloc(sizeof(char) * (word_list->size + 1));
	char *string_start = string;

	for(infos *ac_char = word_list->first ; ac_char != NULL ; ac_char = ac_char->nxt)
	{
		if(ac_char->type == WORD)
		{
			double *scaled_char = matrix_scale(ac_char->pos, (int)width, (int)ac_char->width, (int)ac_char->height, 24, 24);
			*(string++) = (char)feed_forward(net, scaled_char);
		}
		else if (ac_char->type == SPACE)
			*(string++) = ' ';
		else if (ac_char->type == NEW_LINE)
			*(string++) = '\n';
	}

	WL_free(word_list);
	*(string++) = '\0';
	return (string_start);
}

void string_to_file(char *filename, char *string)
{
	if( filename && string)
	{
		char* save_name = malloc(sizeof(char)* (strlen(filename)+1) );
		*save_name = *filename;
		char *save_name_start = save_name;
		++filename;
		++save_name;

		for(;*filename != '.'; ++filename)
		{
			*save_name = *filename;
			save_name ++;
		}
		
		*save_name = '.';
                ++save_name;
		*save_name = 't';
		++save_name;
		*save_name ='x';
		++save_name;
		*save_name = 't';
		printf("%s \n", save_name_start);
		FILE *f = fopen(save_name_start, "w");
		if(f)
		{
			fprintf(f,string);
			fclose(f);
		}	
	}
}
