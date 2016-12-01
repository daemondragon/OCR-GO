#include "img2txt.h"
#include <stdlib.h>
#include <stdio.h>
#include "save_load_network.h"
#include "testing_img2txt.h"
void test_string()
{
        int l = 40;
        int h = 20;

        double *matrix = file_to_matrix_grey("./image_test/test_cut.png",0,&l,&h);
	neural_network_t *net = load_neural_network("./net/83,585\%.nt");
	printf( img_to_string(matrix, l, h, 1, 0.1, net) );
}
