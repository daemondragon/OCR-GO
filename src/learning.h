#ifndef LEARNING_H
#define LEARNING_H

#include <stdint.h>

#include "neural_network.h"

typedef struct
{
    double      *inputs;//Preallocated array of inputs
    uint32_t    answer;
} neural_exemple_t;

void    learn(neural_network_t *net,
              neural_exemple_t *exemples,
              uint32_t nb_exemples,
              uint32_t nb_iterations,
              float learning_rate);

float   neural_network_results(neural_network_t *net,
                               neural_exemple_t *exemples,
                               uint32_t nb_exemples);

#endif
