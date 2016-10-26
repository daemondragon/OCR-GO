#ifndef NEURAL_LAYER_H
#define NEURAL_LAYER_H

/*
** This neural network have in every layer a sigmoid function for activation,
** except in the output layer, which have a softmax layer
*/

#include <stdint.h>

typedef struct
{
    uint32_t    nb_neurons;
    uint32_t    total_connections;//nb_neurons * nb_inputs_neurons
    double      *outputs;
    double      *inputs_weights;
    double      *biaises;
    double      *errors;
} neural_layer_t;

neural_layer_t  *create_neural_layer(uint32_t nb_neurons,
                                     uint32_t nb_inputs_neurons);
void            delete_neural_layer(neural_layer_t *layer);

#endif
