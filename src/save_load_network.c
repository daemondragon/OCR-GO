#include "save_load_network.h"

#include <stdlib.h>
#include <stdio.h>

neural_network_t* load_neural_network(char filename[])
{
    FILE *file = fopen(filename, "r");
    if (!file)
        return (NULL);

    uint32_t nb_layers;
    fread(&nb_layers, sizeof(uint32_t), 1, file);

    uint32_t *nb_neurons_per_layer = malloc(sizeof(uint32_t) *
                                                  nb_layers);
    if (!nb_neurons_per_layer)
        return (NULL);

    fread(nb_neurons_per_layer, sizeof(uint32_t), nb_layers, file);
    neural_network_t *net = create_neural_network(nb_layers,
                                                  nb_neurons_per_layer);

    free(nb_neurons_per_layer);
    if (!net)
        return (NULL);

    for (uint32_t i = 1; i < net->nb_layers; i++)
    {
        fread(net->layers[i]->inputs_weights, sizeof(double),
              net->layers[i]->total_connections, file);

        fread(net->layers[i]->biaises, sizeof(double),
              net->layers[i]->nb_neurons, file);
    }

    fclose(file);
    return (net);
}

char save_neural_network(neural_network_t* net, char filename[])
{
    if (!net)
        return (0);

    FILE *file = fopen(filename, "w+");
    if (!file)
        return (0);

    fwrite(&net->nb_layers, sizeof(uint32_t), 1, file);
    for (uint32_t i = 0; i < net->nb_layers; i++)
        fwrite(&net->layers[i]->nb_neurons, sizeof(uint32_t), 1, file);

    //Write biais and weights
    for (uint32_t i = 1; i < net->nb_layers; i++)
    {
        fwrite(net->layers[i]->inputs_weights, sizeof(double),
               net->layers[i]->total_connections, file);

        fwrite(net->layers[i]->biaises, sizeof(double),
               net->layers[i]->nb_neurons, file);
    }

	fclose(file);
	return (1);
}
