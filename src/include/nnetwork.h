#ifndef NNETWORK_H
#define NNETWORK_H

#include <stdint.h>
#include <stdlib.h>
#include "const.h"
#include <string.h>
#include <ncurses.h>


enum activation_function 
{
	ELU,
	GLU,
	CELU,
	GELU,
	RELU,
	RELU6,
	SELU,
	SILU,
	SOFTMAX,
	EXPONENTIAL,
	HARD_SHRINK,
	SIGMOID,
	HARD_SIGMOID,
	LOG_SIGMOID,
	LOG_SOFTMAX,
	HARD_SILU,
	LEAKY_RELU,
	LINEAR,
	TANH
};


enum layer_type
{
	FLATTEN,
	DENSE
};


struct n_network
{
	char* name;
	struct n_layer* layer;
	uint32_t accuracy;
};


struct n_layer
{
	char* name;
	enum layer_type type;
	uint8_t neuron_count;
	enum activation_function act_function;
};


/*
@param [in] char* -> network name
@param [in/out] struct n_network* -> network pointer...
*/
void createNetwork(char*, struct n_network*);

/*
@param [in] int -> index of the network to be deleted
*/
void deleteNetwork(int);

/*
@param [in/out] struct n_network* -> pointer to network about to be expanded
*/
void addLayer(struct n_network*);

/*
@param [in] struct n_network* -> network containing the layer about to be removed
*/
void removeLayer(struct n_network*);

/*
@param [in] char* -> pointer to the network name
*/
void getNetworkName(char*);

void printNetwork(struct n_network*, int, int);

#endif