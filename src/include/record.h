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
	uint32_t activationFunction;
	uint8_t minLayerCount;
	uint8_t maxLayerCount;
	uint8_t minNeuronCount;
	uint8_t maxNeuronCount;
	uint8_t minEpochSize;
	uint8_t maxEpochSize;
	uint8_t minBatchSize;
	uint8_t maxBatchSize;
	// use OHE

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