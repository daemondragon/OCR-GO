#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "neural_network.h"
#include "save_load_network.h"
#include "feed_forward.h"
#include "back_propagation.h"

void    print_network(neural_network_t *net, char show_errors)
{
    if (!net)
        return;

    for (int l = (int)net->nb_layers - 1; l >= 0; l--)
    {
        for (uint32_t i = 0; i < net->layers[l]->nb_neurons; i++)
            printf("%f ", net->layers[l]->outputs[i]);

        if (show_errors)
        {
            printf("\t\terrors: ");
            for (uint32_t i = 0; i < net->layers[l]->nb_neurons; i++)
                printf("%f ", net->layers[l]->errors[i]);
        }
        printf("\n");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
        printf("%s ", argv[i]);
    //creation
    uint32_t neurons[] = {2, 3, 2};
    uint32_t nb_layers = 3;
    char operation[] = "a != b";
    neural_network_t* net = create_neural_network(nb_layers, neurons);

    //initialisation
    initialize_weights_and_biaises(net, time(NULL));

    double inputs[4][2] = {{0, 0}, {1, 0}, {0, 1}, {1, 1}};

    printf("debut: %s\n", operation);
    for (int i = 0; i < 4; i++)
        printf("%1.f %1.f : %d\n", inputs[i % 4][0], inputs[i % 4][1],
                                   feed_forward(net, inputs[i % 4]));

    for (int i = 0; i < 10000; i++)
    {
        int exemple = rand() % 4;
        feed_forward(net, inputs[exemple]);
        back_propagation(net, 0.1, inputs[exemple][0] != inputs[exemple][1]);
    }

    printf("\nresultats: %s\n", operation);
    for (int i = 0; i < 4; i++)
        printf("%1.f %1.f : %d\n", inputs[i % 4][0], inputs[i % 4][1],
                                   feed_forward(net, inputs[i % 4]));

    save_neural_network(net, "net.nt");
    neural_network_t *xor_saved = load_neural_network("net.nt");

    printf("\nsaved resultats: %s\n", operation);
    for (int i = 0; i < 4; i++)
        printf("%1.f %1.f : %d\n", inputs[i % 4][0], inputs[i % 4][1],
                                   feed_forward(xor_saved, inputs[i % 4]));

    delete_neural_network(net);

    return (0);
}
