#ifndef SAVE_LOAD_NETWORK_H
#define SAVE_LOAD_NETWORK_H

#include "neural_network.h"

neural_network_t*   load_neural_network(char filename[]);
char                save_neural_network(neural_network_t* net,
                                        char filename[]);

#endif
