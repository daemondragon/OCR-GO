#include "neural_network.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

neural_network_t* create_neural_network(uint32_t nb_layers,
                                        uint32_t *nb_neurons_per_layer)
{
    #ifdef DEBUG
    printf("Neural network creation...");
    #endif

    if (nb_layers <= 0)
    {
        #ifdef DEBUG
        printf("Failed (0)\n");
        #endif
        return (NULL);
    }

    neural_network_t *neural = malloc(sizeof(neural_network_t));
    if (!neural)
    {
        #ifdef DEBUG
        printf("Failed (1)\n");
        #endif
        return (NULL);
    }

    neural->nb_layers = nb_layers;
    neural->layers = malloc(sizeof(neural_layer_t*) * nb_layers);
    if (!neural->layers)
    {
        free(neural);
        #ifdef DEBUG
        printf("Failed (2)\n");
        #endif
        return (NULL);
    }

    for (int i = 0; i < (int)nb_layers; i++)
    {
        neural->layers[i] = create_neural_layer(nb_neurons_per_layer[i],
            (i <= 0 ? 0 : nb_neurons_per_layer[i - 1]));

        if (!neural->layers[i])
        {
            for (i--; i >= 0; i--)
                delete_neural_layer(neural->layers[i]);
            free(neural->layers);
            free(neural);

            #ifdef DEBUG
            printf("Failed (3)\n");
            #endif

            return (NULL);
        }
    }

    #ifdef DEBUG
    printf("Done\n");
    #endif
    return (neural);
}

void delete_neural_network(neural_network_t *neural)
{

    #ifdef DEBUG
    printf("Delete neural network...");
    #endif

    if (!neural)
        return;

    for (uint32_t i = 0; i < neural->nb_layers; i++)
        delete_neural_layer(neural->layers[i]);

    free(neural->layers);
    free(neural);

    #ifdef DEBUG
    printf("Done\n");
    #endif
}

void initialize_weights_and_biaises(neural_network_t *net, uint32_t seed)
{
    #ifdef DEBUG
    printf("Neural network weigths initialization...");
    #endif

    if (!net)
        return;

    srand(seed);
    for (uint32_t l = 1 ; l < net->nb_layers ; l++)
    {
        double size = 2.0 * sqrt(6.0 / (net->layers[l - 1]->nb_neurons +
                                        net->layers[l]->nb_neurons));
        for (uint32_t c = 0 ; c < net->layers[l]->total_connections; c++)
            net->layers[l]->inputs_weights[c] =
               ((rand() % 10000) / 10000.0) * size - size / 2.0;

        for (uint32_t n = 0 ; n < net->layers[l]->nb_neurons ; n++)
            net->layers[l]->biaises[n] = 0.0;
    }

    #ifdef DEBUG
    printf("Done\n");
    #endif
}

uint32_t get_connection_index(neural_layer_t *layer,
                              uint32_t neuron,
                              uint32_t next_layer_neuron)
{
    return (layer->nb_neurons * next_layer_neuron + neuron);
}
