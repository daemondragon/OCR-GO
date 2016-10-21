#include "learning.h"

#include <stdio.h>

#include "back_propagation.h"
#include "feed_forward.h"

void learn(neural_network_t *net,
           neural_exemple_t *exemples,
           uint32_t nb_exemples,
           uint32_t nb_iterations,
           float learning_rate)
{
    if (!net || !exemples)
        return;

    #ifdef DEBUG
    printf("Start neural network learning (%d exemples, %d iterations)...\n",
            nb_exemples, nb_iterations);
    #endif

    float individual_learning_rate = learning_rate / nb_exemples;

    for (uint32_t i = 0; i < nb_iterations; ++i)
    {
        for (uint32_t j = 0; j < nb_exemples; ++j)
        {
            feed_forward(net, exemples[j].inputs);
            back_propagation(net,
                             individual_learning_rate,
                             exemples[j].answer);
        }
    }
    #ifdef DEBUG
    printf("End of neural network learning...\n");
    #endif
}

float neural_network_results(neural_network_t *net,
                             neural_exemple_t *exemples,
                             uint32_t nb_exemples)
{
    uint32_t nb_valid_answers = 0;
    for (uint32_t i = 0; i < nb_exemples; ++i)
    {
        nb_valid_answers +=
            feed_forward(net, exemples[i].inputs) == exemples[i].answer;
    }

    float result = (float)nb_valid_answers / (float)nb_exemples;
    #ifdef DEBUG
    printf("Neural network pass %.3f\%% of the tests...\n", result * 100);
    #endif
    return (result);
}
