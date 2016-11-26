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
void train_tchou_tchou()
{
    
    uint32_t nb_neurons_per_layer[] = {576, 1024, 128};
    neural_network_t *net = create_neural_network(3, nb_neurons_per_layer);
    if (!net)
    {
        printf("Neural network alloc failed\n");
        return;
    }
    
    initialize_weights_and_biaises(net, 0);
    
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
			  1, 1000, 10);
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
	{"mat_copy",    "test for copying matrix",      test_mat_copy},
	{"train",       "train a neural network",       train_tchou_tchou},
	{"rotation",	"make a rotation",				test_rotation}
	};
    size_t nb_arguments = 6;

    if (argc > 1)
    {
        for (size_t i = 0; i < nb_arguments; i++)
        {
            if (is_same_string(argv[1], arguments[i].arg))
            {
                if (arguments[i].fun)
                    arguments[i].fun();
                else
                    printf("Error in arg %s : function is NULL\n", argv[1]);
                break;
            }
        }
    }
    else
    {
        printf("%s arguments:\n", argv[0]);
        for (size_t i = 0; i < nb_arguments; i++)
            printf("    %s - %s\n", arguments[i].arg,
                                    arguments[i].description);

        run_window(argc, argv);
    }

    return (0);
}
