#ifndef FEED_FORWARD_H
#define FEED_FORWARD_H

#include "neural_network.h"

// inputs size need to be at least the number of neurons of the first layer
// return the neuron with the maximum output (the answer of the network)
// inputs will NOT be free
uint32_t    feed_forward(neural_network_t *net, double *inputs);

#endif
