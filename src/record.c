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