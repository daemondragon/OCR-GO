#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "neural_layer.h"

typedef struct
{
    uint32_t        nb_layers;
    neural_layer_t  **layers;

} neural_network_t;

neural_network_t* create_neural_network(uint32_t nb_layers,
                                        uint32_t *nb_neurons_per_layer);
void              delete_neural_network(neural_network_t *neural);


void              initialize_weights_and_biaises(neural_network_t *net,
                                                 uint32_t seed);

//NOT intended to be used by other file than those related to the network.
uint32_t         get_connection_index(neural_layer_t *layer,
                                      uint32_t neuron,
                                      uint32_t next_layer_neuron);

#endif
