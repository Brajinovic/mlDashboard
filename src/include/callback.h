#ifndef CALLBACK_H
#define CALLBACK_H

#include "menu.h"
#include "record.h"

extern int row;
extern int col;

void callbackStartLearning(void);

void callbackNewNetworkScratch(void);
void callbackNewNetworkTemplate(void);

/*
new network config
*/
void callbackMinNoHiddenLayers(void);
void callbackMaxNoHiddenLayers(void);
void callbackMinNumberNeurons(void);
void callbackMaxNumberNeurons(void);
void callbackMinEpochSize(void);
void callbackMaxEpochSize(void);
void callbackMinBatchSize(void);
void callbackMaxBatchSize(void);
void callbackActivationFunctions(void);


/*
activation function selection
*/
void callbackRelu(void);
void callbackSelu(void);
void callbackElu(void);
void callbackCelu(void);
void callbackGlu(void);
void callbackGelu(void);
void callbackSigmoid(void);
void callbackSoftmax(void);
void callbackSoftplus(void);
void callbackSoftSign(void);
void callbackTanh(void);
void callbackExponential(void); 
void callbackLinear(void);
void callbackLogSigmoid(void);
void callbackExponential(void);


void callbackLevelUp(void);
void callbackExit(void);


#endif