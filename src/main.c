#include <stdlib.h>
#include <stdio.h>

#include "show_xor.h"
#include "load_exemples.h"
#include "window.h"
#include "testing_cut.h"

#include "image_to_matrix.h"
#include "filters.h"

#include "load_exemples.h"
#include "rotation.h"

#include "testing_img2txt.h"
void train_tchou_tchou()
{
    
    neural_network_t *net = load_neural_network("net/tchou_tchou.nt");
    if (!net)
    {
        printf("Neural network alloc failed\n");
        return;
    }

    uint32_t nb_train_data;
    uint32_t nb_validation_data;

    neural_exemple_t *train_data = load_exemples("./images/test/",
                                load_matrix_grey,
                                &nb_train_data);
   neural_exemple_t *validation_data = load_exemples("./images/validation/",
                                load_matrix_grey,
                                &nb_validation_data);

    printf("load finished\n");
    train(net, train_data, nb_train_data, validation_data, nb_validation_data,
			  1, 1000, 7);
}

void get_neural_advanced_result()
{

    neural_network_t *net = load_neural_network("./net/tchou_tchou.nt");
    if (!net)
    {
        printf("Neural network alloc failed\n");
        return;
    }
    
    uint32_t nb_train_data;

    neural_exemple_t *train_data = load_exemples("./images/test/",
                                load_matrix_grey,
                                &nb_train_data);

    printf("load finished\n");

    printf("global result: %f\n",
            neural_network_results(net, train_data, nb_train_data) * 100);

    printf("specific result:\n");
    float *result = neural_network_advanced_results(net, train_data, nb_train_data);
    if (result)
    {
        for (int i = 0; i < 128; ++i)
            if (result[i] > 0.0f)
                printf("%c : %3.3f\n", i, result[i] * 100);
    }
}

char is_same_string(char *s1, char *s2)
{
    while (*s1 != '\0' && *s2 != '\0')
    {
        if (*s1 != *s2)
            return (0);
        else
        {
            ++s1;
            ++s2;
        }
    }
    return (*s1 == *s2);
}

typedef struct
{
    char *arg;
    char *description;
    void (*fun)(void);
} argument_t;

int main(int argc, char *argv[])
{
    argument_t  arguments[] = {
    {"xor",         "show neural network xor",      show_xor},
    {"filter",      "test for filters",             test_filters},
	{"pcut",        "pretty test for cutting",      show_cutting},
	{"test_s",	"revoi la string comprise par le neural", test_string},
	{"test_save",	"test la sauvegarde de resultat"    , test_save},
	{"mat_copy",    "test for copying matrix",      test_mat_copy},
	{"train",       "train a neural network",       train_tchou_tchou},
	{"rotation",	"make a rotation",				test_rotation},
	{"net_result",  "get neural network result",    get_neural_advanced_result}
	};
    size_t nb_arguments = 9;

    if (argc > 1)
    {
        size_t to_call;
        for (to_call = 0; to_call < nb_arguments &&
                          !is_same_string(argv[1], arguments[to_call].arg);
             to_call++) {}
        
        if (to_call < nb_arguments)
        {
            if (arguments[to_call].fun)
                arguments[to_call].fun();
            else
            {
                printf("Error in arg %s : function is NULL\n", argv[1]);
            }
        }
        else
        {//Error
            printf("Error: no matching argument found for %s\n", argv[1]);
            printf("%s arguments:\n", argv[0]);
            for (size_t i = 0; i < nb_arguments; i++)
                printf("    %s - %s\n", arguments[i].arg,
                                        arguments[i].description);
        }
    }
    else
    {
        printf("Run default program\n");
        run_window(argc, argv);
    }

    return (0);
}
