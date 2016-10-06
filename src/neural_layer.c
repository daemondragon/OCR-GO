#include "neural_layer.h"

#include <stdlib.h>

neural_layer_t *create_neural_layer(uint32_t nb_neurons,
                                    uint32_t nb_inputs_neurons)
{
    if (nb_neurons <= 0)
        return (0);

    neural_layer_t *layer = malloc(sizeof(neural_layer_t));
    if (!layer)
        return (NULL);

    layer->nb_neurons = nb_neurons;
    layer->total_connections = nb_neurons * nb_inputs_neurons;

    layer->inputs_weights = NULL;
    layer->biaises = NULL;
    //The first layer don't have any weighted input or biaises
    if (layer->total_connections > 0)
    {
        layer->inputs_weights = malloc(sizeof(double) *
                                        layer->total_connections);
        layer->biaises = malloc(sizeof(double) * nb_neurons);
    }

    layer->outputs = malloc(sizeof(double) * nb_neurons);
    layer->errors  = malloc(sizeof(double) * nb_neurons);

    if (!layer->outputs || ! layer->errors ||
        (layer->total_connections > 0 &&
         (!layer->inputs_weights || !layer->biaises)))
    {
        delete_neural_layer(layer);
        return (NULL);
    }

    return (layer);
}

void delete_neural_layer(neural_layer_t *layer)
{
    if (!layer)
        return;

    if (layer->inputs_weights)
        free(layer->inputs_weights);
    if (layer->biaises)
        free(layer->biaises);
    if (layer->outputs)
        free(layer->outputs);
    if (layer->errors)
        free(layer->errors);

    free(layer);
}
