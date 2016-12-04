#include "learning.h"

#include <stdlib.h>
#include <stdio.h>

#include "save_load_network.h"
#include "back_propagation.h"
#include "feed_forward.h"

//  If current_iteration < max_iterations * STOP_PERCENT; continue learning
// Even if the neural network may overlearn
#define STOP_PERCENT    0.97
//To stop overlearning (increase to better stop)
#define EPSILON         0.0001

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

float* neural_network_advanced_results(neural_network_t *net,
                                       neural_exemple_t *exemples,
                                       uint32_t nb_exemples)
{
    uint32_t nb_neurons = net->layers[net->nb_layers - 1]->nb_neurons;
    uint32_t* max = malloc(sizeof(uint32_t) * nb_neurons);
    uint32_t* actual = malloc(sizeof(uint32_t) * nb_neurons);
    float* result = malloc(sizeof(float) * nb_neurons);
    if (!max || !actual || !result)
    {
        free(max);
        free(actual);
        free(result);
        return (NULL);
    }

    for (uint32_t i = 0; i < nb_neurons; ++i)
    {
        max[i] = 0;
        actual[i] = 0;
        result[i] = 0;
    }

    for (uint32_t i = 0; i < nb_exemples; ++i)
    {
        max[exemples[i].answer]++;
         actual[exemples[i].answer] +=
            feed_forward(net, exemples[i].inputs) == exemples[i].answer;
    }

    for (uint32_t i = 0; i < nb_neurons; ++i)
        result[i] = max[i] ? actual[i] * 1.0 / max[i] : 0;

    free(max);
    free(actual);

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

    printf("STOP_PERCENT %3.3f | EPSILON %3.3f\n",
            STOP_PERCENT,        EPSILON * 100);

    float last_result = neural_network_results(net,
				train_data, nb_train_data);
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

        continue_training =
            (current_result < STOP_PERCENT ||
            (current_result >= last_result &&
                current_result - last_result > EPSILON)) &&
            iteration < max_iterations;

        #ifdef DEBUG
        printf("Iteration %d: score %2.3f\%% | delta %f\n",
                iteration, current_result * 100, current_result -last_result);
        #endif

        if (!continue_training)
        {
            #ifdef DEBUG
            printf("Stop training asked : creating
				new network and starting over\n");
            #endif
            uint32_t nb_layers = net->nb_layers;
            uint32_t *nb_neurons_per_layer=malloc(sizeof(uint32_t)*nb_layers);
            if (nb_neurons_per_layer)
            {
                for (uint32_t i = 0; i < nb_layers; ++i)
                    nb_neurons_per_layer[i] = net->layers[i]->nb_neurons;
                delete_neural_network(net);
                net = create_neural_network(nb_layers, nb_neurons_per_layer);
                free(nb_neurons_per_layer);
                if (net)
                {
                    initialize_weights_and_biaises(net, iteration);
                    iteration += 100;
                    continue_training = 1;
                }
            }
        }

        iteration++;
        last_result = current_result;
    } while (continue_training && iteration < max_iterations);
}
