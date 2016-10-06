#ifndef BACK_PROPAGATION_H
#define BACK_PROPAGATION_H

#include "neural_network.h"

/*
**  desired_neuron : the neuron which where expected to be activate after
**                   feedforward
**  learning_rate : [0, 1], close to 0 for a better learning
*/
void    back_propagation(neural_network_t *net,
                         double learning_rate,
                         uint32_t desired_neuron);

#endif
