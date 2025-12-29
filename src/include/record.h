#ifndef RECORD_H
#define RECORD_H

#include <ncurses.h>
#include "menu.h"
#include <time.h>
#include <stdint.h>

extern int row;
extern int col;

struct learning_parameter_record
{
	uint64_t id;
	// ohe
	uint32_t activationFunction;
	uint16_t minLayerCount;
	uint16_t maxLayerCount;
	uint16_t minNeuronCount;
	uint16_t maxNeuronCount;
	uint16_t minEpochSize;
	uint16_t maxEpochSize;
	uint16_t minBatchSize;
	uint16_t maxBatchSize;
	

};


void refreshMenu(struct menu_template*, struct learning_parameter_record*);

/*
Write learning parameters to file. This should occur right before you exit the 
network config menu. Use the current time as an uID for the configuration.
*/
void writeConfig(struct learning_parameter_record*);
void readConfig(FILE*, struct learning_parameter_record*);

void printConfig(int col, struct learning_parameter_record*);
void printActivationFunctions(int, int);

void fillList(FILE*, struct menu_template*);

#endif