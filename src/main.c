#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "neural_network.h"
#include "save_load_network.h"
#include "feed_forward.h"
#include "back_propagation.h"
#include "learning.h"
#include "window.h"
#include "testing_cut.h"

void    print_result(neural_network_t *net)
{
    double inputs[4][2] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};

    printf("+-+-+-+\n");
    printf("| |0|1|\n");
    printf("+-+-+-+\n");
    printf("|0|%d|%d|\n", feed_forward(net, inputs[0]),
                          feed_forward(net, inputs[1]));
    printf("+-+-+-+\n");
    printf("|1|%d|%d|\n", feed_forward(net, inputs[2]),
                          feed_forward(net, inputs[3]));
    printf("+-+-+-+\n");
}

void    show_xor()
{
    uint32_t neurons[] = {2, 3, 2};
    uint32_t nb_layers = 3;

    printf("Xor with %d layers and:\n", nb_layers);
    for (uint32_t i = 0; i < nb_layers; ++i)
        printf("%d neurons in layer(%d)\n",neurons[i],i);

    neural_network_t* net = create_neural_network(nb_layers, neurons);

    initialize_weights_and_biaises(net, time(NULL));

    neural_exemple_t exemples[4];
    for (int i = 0 ; i < 4; ++i)
    {
        exemples[i].inputs = malloc(sizeof(double) * 2);
        exemples[i].inputs[0] = i / 2;
        exemples[i].inputs[1] = i % 2;
        exemples[i].answer = (i == 1 || i == 2);
    }

    printf("Neural network start result...\n");
    print_result(net);

    neural_network_results(net, exemples, 4);
    learn(net, exemples, 4, 10000, 0.1);

    printf("Neural network learning result...\n");
    print_result(net);
    neural_network_results(net, exemples, 4);

    save_neural_network(net, "net.nt");
    neural_network_t *xor_saved = load_neural_network("net.nt");

    printf("Neural network saved result...\n");
    print_result(xor_saved);
    neural_network_results(net, exemples, 4);

    delete_neural_network(net);
    delete_neural_network(xor_saved);
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
    argument_t  arguments[] = {{"xor", "show neural network xor", show_xor},
			       {"tcut", "rapid test for cutting",test_cut    }};
    size_t nb_arguments = 2;
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
