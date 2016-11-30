#include <stdio.h>
#include <stdlib.h>
#include <img2txt.h>

char* img_to_string(double *matrix, size_t width , size_t height, int threshold, float height_rate,neural_network_t *net)
{
  W_list *word_list = cutting(matrix, width, height, threshold, height_rate);
  char *string = malloc(sizeof(char)*word_list->size);


  for(infos *ac_char = word_list->first ; ac_char != NULL ; ac_char = ac_char->nxt)
    {
      if(ac_char->type == WORD)
	{
	  double *scaled_char = matrix-scale(ac_char->pos, (int)ac_char->width, (int)width, (int)height, 24, 24);
	  string += (char)feed_forward(net, scaled_char);
	}
      else if (ac_char->type == SPACE)
	{
	  string += " ";
	}
      else if (ac_char->type == NEW_LINE)
	{
	  string += "\n"
	}
    }
  W_free(word_list);
  return string;
}
