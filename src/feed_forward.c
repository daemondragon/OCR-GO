#include "feed_forward.h"

#include <math.h>

static void clear_previous_outputs(neural_network_t *net)
{
    for (uint32_t i = 0; i < net->nb_layers; ++i)
        for (uint32_t j = 0; j < net->layers[i]->nb_neurons; ++j)
            net->layers[i]->outputs[j] = 0.0;
}

static void apply_inputs(neural_network_t *net, double *inputs)
{
    neural_layer_t *layer = net->layers[0];

    for (uint32_t i = 0 ; i < layer->nb_neurons ; ++i)
        layer->outputs[i] = inputs[i];
}

// Calc the temp input that can be used by apply_sigmoid_on_layer
// and softmax functions (used to simplifing code)
static void calc_temp_layer_outputs(neural_network_t *net, int l)
{
    neural_layer_t *layer = net->layers[l];
    neural_layer_t *previous_layer = net->layers[l - 1];

    for (uint32_t i = 0 ; i < layer->nb_neurons ; ++i)
    {
        layer->outputs[i] = layer->biaises[i];
        for (uint32_t j = 0 ; j < previous_layer->nb_neurons ; ++j)
        {
            layer->outputs[i] += previous_layer->outputs[j] *
                layer->inputs_weights[
                    get_connection_index(previous_layer, j, i)];
        }
    }
}

static void apply_sigmoid_on_layer(neural_network_t *net, uint32_t l)
{
    calc_temp_layer_outputs(net, l);

    for (uint32_t i = 0; i < net->layers[l]->nb_neurons; ++i)
        net->layers[l]->outputs[i] =
            1.0 / (1.0 + exp(-net->layers[l]->outputs[i]));
}

static void apply_softmax_on_layer(neural_network_t *net, uint32_t l)
{
    calc_temp_layer_outputs(net, l);

    double sum = 0.0;
    for (uint32_t i = 0; i < net->layers[l]->nb_neurons; ++i)
        sum += exp(net->layers[l]->outputs[i]);

    for (uint32_t i = 0; i < net->layers[l]->nb_neurons; ++i)
        net->layers[l]->outputs[i] = exp(net->layers[l]->outputs[i]) / sum;
}

static uint32_t get_answer(neural_layer_t *last_layer)
{
    double max = last_layer->outputs[0];
    uint32_t answer = 0;

    for (uint32_t i = 1 ; i < last_layer->nb_neurons ; ++i)
    {
        if (last_layer->outputs[i] > max)
        {
            max = last_layer->outputs[i];
            answer = i;
        }
    }

    return (answer);
}

uint32_t feed_forward(neural_network_t *net, double *inputs)
{
    if (!net || !inputs)
        return (0);

    clear_previous_outputs(net);
    apply_inputs(net, inputs);

    for (uint32_t i = 1; i < net->nb_layers - 1; ++i)
        apply_sigmoid_on_layer(net, i);
    apply_softmax_on_layer(net, net->nb_layers - 1);

    return (get_answer(net->layers[net->nb_layers - 1]));
}

