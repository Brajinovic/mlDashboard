#ifndef RECORD_H
#define RECORD_H

#include <ncurses.h>
#include "menu.h"
#include <time.h>

extern int row;
extern int col;

struct learning_parameter_record
{
	long int id;
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
void writeConfig(struct learning_parameter_record*);
void readConfig(FILE*, struct learning_parameter_record*);

void printConfig(int col, struct learning_parameter_record*);
void printActivationFunctions(int, int);

#endif