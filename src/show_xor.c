#include "show_xor.h"

#include <stdlib.h>
#include <stdio.h>

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

