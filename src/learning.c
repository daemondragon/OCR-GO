#include "learning.h"

#include <stdio.h>

#include "save_load_network.h"
#include "back_propagation.h"
#include "feed_forward.h"

//To stop overlearning (increase to better stop)
#define EPSILON 0.01

void learn(neural_network_t *net,
           neural_exemple_t *exemples,
           uint32_t nb_exemples,
           uint32_t nb_iterations,
           float learning_rate)
{
    if (!net || !exemples)
        return;

    #ifdef DEBUG
    printf("Neural network learning (%d exemples, %d iterations)...",
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
    printf("Done\n");
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

void train(neural_network_t *net,
		   neural_exemple_t *train_data, uint32_t nb_train_data,
		   neural_exemple_t *validation_data, uint32_t nb_validation_data,
		   uint32_t nb_iterations_per_train, uint32_t max_iterations,
		   float learning_rate)
{
    if (!net ||
        !train_data || !nb_train_data ||
        !validation_data || !nb_validation_data)
        return;

    float last_result = neural_network_results(net, train_data, nb_train_data);
    char        continue_training = 1;
    uint32_t    iteration = 0;
    char        net_name[16] = "net/00000000.nt";

    do
    {
        learn(net, train_data, nb_train_data,
              nb_iterations_per_train, learning_rate);

        //Save it
        uint32_t temp = iteration;
        for (int i = 11; i > 3; --i)
        {
            net_name[i] = temp % 10 + '0';
            temp /= 10;
        }
        #ifndef DEBUG
        save_neural_network(net, net_name);
        #else
        if (!save_neural_network(net, net_name))
            printf("Save failed : it:%d, name: %s\n", iteration, net_name);
        #endif

        //Test network learning
        float current_result =
            neural_network_results(net, validation_data, nb_validation_data);
        continue_training = (last_result <= current_result) ||
            (current_result - last_result > EPSILON);
        #ifdef DEBUG
        printf("Iteration %d: score %2.3f\%%\n", iteration, current_result);
        #endif
        iteration++;
    } while (continue_training && iteration < max_iterations);
}
