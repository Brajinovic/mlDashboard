#include "record.h"


void refreshMenu(struct menu_template* menu, struct learning_parameter_record* parameters)
{
	char str[15];

	sprintf(str, "%d", parameters->minLayerCount);
	// only do the memcpy if the default value changed
	if (*str != '0')
		memcpy(menu->items[2]->name + PARAMETER_VALUE_OFFSET, str, 10);

	sprintf(str, "%d", parameters->maxLayerCount);
	// only do the memcpy if the default value changed
	if (*str != '0')
		memcpy(menu->items[3]->name + PARAMETER_VALUE_OFFSET, str, 10);


	sprintf(str, "%d", parameters->minNeuronCount);
	if (*str != '0')
		memcpy(menu->items[4]->name + PARAMETER_VALUE_OFFSET, str, 10);

	sprintf(str, "%d", parameters->maxNeuronCount);
	if (*str != '0')
		memcpy(menu->items[5]->name + PARAMETER_VALUE_OFFSET, str, 10);


	sprintf(str, "%d", parameters->minEpochSize);
	if (*str != '0')
		memcpy(menu->items[6]->name + PARAMETER_VALUE_OFFSET, str, 10);

	sprintf(str, "%d", parameters->maxEpochSize);
	if (*str != '0')
		memcpy(menu->items[7]->name + PARAMETER_VALUE_OFFSET, str, 10);


	sprintf(str, "%d", parameters->minBatchSize);
	if (*str != '0')
		memcpy(menu->items[8]->name + PARAMETER_VALUE_OFFSET, str, 10);

	sprintf(str, "%d", parameters->maxBatchSize);
	if (*str != '0')
		memcpy(menu->items[9]->name + PARAMETER_VALUE_OFFSET, str, 10);

	sprintf(str, "%d", parameters->activationFunction);
	
	if (*str == '0')
		sprintf(str, "Relu (Default)");
	else
		sprintf(str, "Top right!    ");

	memcpy(menu->items[10]->name + PARAMETER_VALUE_OFFSET, str, 14);

	
}

// create a new menu related to the selected activation functions?

void writeConfig(struct learning_parameter_record* parameters)
{
	FILE* fptr;

    fptr = fopen("file.txt", "a+");

    if (fptr == NULL) 
        printf("The file is not opened.");
    else
    {
    	fprintf(fptr, "ID: %ld\n"
    			   "\tminLayerCount: \t\t\t%d\n"
    			   "\tmaxLayerCount: \t\t\t%d\n"
    			   "\tminNeuronCount: \t\t%d\n"
    			   "\tmaxNeuronCount: \t\t%d\n"
    			   "\tminEpochSize: \t\t\t%d\n"
    			   "\tmaxEpochSize: \t\t\t%d\n"
    			   "\tminBatchSize: \t\t\t%d\n"
    			   "\tmaxBatchSize: \t\t\t%d\n"
    			   "\tactivationFunction(s): \t%d\n\n",
    			   time(0),
    			   parameters->minLayerCount == 0 ? 2 : parameters->minLayerCount,
    			   parameters->maxLayerCount == 0 ? 8 : parameters->maxLayerCount,
    			   parameters->minNeuronCount == 0 ? 16 : parameters->minNeuronCount,
    			   parameters->maxNeuronCount == 0 ? 128 : parameters->maxNeuronCount,
    			   parameters->minEpochSize == 0 ? 100 : parameters->minEpochSize,
    			   parameters->maxEpochSize == 0 ? 1000 : parameters->maxEpochSize,
    			   parameters->minBatchSize == 0 ? 10 : parameters->minBatchSize,
    			   parameters->maxBatchSize == 0 ? 100 : parameters->maxBatchSize,
    			   parameters->activationFunction == 0 ? 1 : parameters->activationFunction);

    	fclose(fptr);
    }
}