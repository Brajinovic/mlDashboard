#ifndef RECORD_H
#define RECORD_H

#include <ncurses.h>
#include "menu.h"


extern int row;
extern int col;

struct learning_parameter_record
{
	int minLayerCount;
	int maxLayerCount;
	int minNeuronCount;
	int maxNeuronCount;
	int minEpochSize;
	int maxEpochSize;
	int minBatchSize;
	int maxBatchSize;
	// use OHE
	int activationFunction;

};


void refreshMenu(struct menu_template*, struct learning_parameter_record*);

/*
Write learning parameters to file. This should occur right before you exit the 
network config menu. Use the current time as an uID for the configuration.
*/
void printToFile(struct learning_parameter_record*);

#endif