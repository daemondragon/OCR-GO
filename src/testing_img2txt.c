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
	neural_network_t *net = load_neural_network("./net/test.nt");
	printf("%s\n", img_to_string(matrix, l, h, 1, 0.1, net) );
}

void test_save()
{
 int l = 40;
        int h = 20;

        double *matrix = file_to_matrix_grey("./image_test/test_cut.png",0,&l,&h);
        neural_network_t *net = load_neural_network("./net/83,585\%.nt");
        string_to_file("./image_test/test_cut.png", img_to_string(matrix, l, h, 1, 0.1, net) );


}
