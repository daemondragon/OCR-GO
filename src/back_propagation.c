#include "back_propagation.h"

#include <math.h>

static double sigmoid_prime(double value)
{
    return (value * (1.0 - value));
}

static void clear_previous_errors(neural_network_t *net)
{
    for (uint32_t i = 0; i < net->nb_layers; i++)
        for (uint32_t j = 0; j < net->layers[i]->nb_neurons; j++)
            net->layers[i]->errors[j] = 0.0;
}

static void calc_output_layer_errors(neural_network_t *net,
                                     unsigned short desired_neuron)
{
    neural_layer_t *layer = net->layers[net->nb_layers - 1];

    for (uint32_t i = 0 ; i < layer->nb_neurons ; i++)
        layer->errors[i] = ((i != desired_neuron ? 0.0 : 1.0) -
                                layer->outputs[i]);
}

static void calc_hidden_layer_errors(neural_network_t *net, uint32_t l)
{
    neural_layer_t *layer = net->layers[l];
    neural_layer_t *next_layer = net->layers[l + 1];

    for (uint32_t i = 0 ; i < next_layer->nb_neurons ; i++)
        for (uint32_t j = 0 ; j < layer->nb_neurons ; j++)
            layer->errors[j] += next_layer->errors[i] *
                next_layer->inputs_weights[
                    get_connection_index(layer, j, i)];

    for (uint32_t j = 0 ; j < layer->nb_neurons ; j++)
        layer->errors[j] *= sigmoid_prime(layer->outputs[j]);
}

static void apply_errors(neural_network_t *net, double learning_rate)
{
    //Update biaises
    for (uint32_t l = 1 ; l < net->nb_layers ; l++)
        for (uint32_t n = 0 ; n < net->layers[l]->nb_neurons ; n++)
            net->layers[l]->biaises[n] +=
                net->layers[l]->errors[n] * learning_rate;

    //Update weight
    for (uint32_t l = 1 ; l < net->nb_layers ; l++)
    {
        for (uint32_t n = 0 ; n < net->layers[l]->nb_neurons ; n++)
        {
            for (uint32_t p_n = 0 ;
                 p_n < net->layers[l - 1]->nb_neurons ;
                 p_n++)
            {
                net->layers[l]->inputs_weights[
                    get_connection_index(net->layers[l - 1], p_n, n)] +=
                        net->layers[l]->errors[n] *
                            net->layers[l - 1]->outputs[p_n] * learning_rate;
            }
        }
    }
}

void back_propagation(neural_network_t *net,
                      double learning_rate,
                      uint32_t desired_neuron)
{
    if (!net)
        return;

    clear_previous_errors(net);

    calc_output_layer_errors(net, desired_neuron);
    for (int32_t i = net->nb_layers - 2 ; i >= 0 ; i--)
        calc_hidden_layer_errors(net, i);

    apply_errors(net, learning_rate);
}
