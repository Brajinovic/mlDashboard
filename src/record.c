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


void readConfig(FILE* fptr, struct learning_parameter_record* parameters)
{
	long int id;
   
    if (fptr == NULL) 
    {
        printf("The file is not opened.");
    	mvprintw(2, 0, "Sth is fucked!");
    	getch();
    }
    else
    {
    	fscanf(fptr, "%*s %ld", &(parameters->id));
    	fscanf(fptr, "%*s %d", &(parameters->minLayerCount));
    	fscanf(fptr, "%*s %d", &(parameters->maxLayerCount));
    	fscanf(fptr, "%*s %d", &(parameters->minNeuronCount));
    	fscanf(fptr, "%*s %d", &(parameters->maxNeuronCount));
    	fscanf(fptr, "%*s %d", &(parameters->minEpochSize));
    	fscanf(fptr, "%*s %d", &(parameters->maxEpochSize));
    	fscanf(fptr, "%*s %d", &(parameters->minBatchSize));
    	fscanf(fptr, "%*s %d", &(parameters->maxBatchSize));
    	fscanf(fptr, "%*s %d", &(parameters->activationFunction));

    }
}


void printConfig(int column, struct learning_parameter_record* config)
{
	mvprintw(2, column, "Active config: ");
	mvprintw(3, column + 5, "ID: \t\t\t%ld", config->id);
	mvprintw(4, column + 5, "minLayerCount:  \t\t%d", config->minLayerCount);
	mvprintw(5, column + 5, "maxLayerCount:  \t\t%d", config->maxLayerCount);
	mvprintw(6, column + 5, "minNeuronCount: \t\t%d", config->minNeuronCount);
	mvprintw(7, column + 5, "maxNeuronCount: \t\t%d", config->maxNeuronCount);
	mvprintw(8, column + 5, "minEpochSize:  \t\t%d", config->minEpochSize);
	mvprintw(9, column + 5, "maxEpochSize:  \t\t%d", config->maxEpochSize);
	mvprintw(10, column + 5, "minBatchSize: \t\t%d", config->minBatchSize);
	mvprintw(11, column + 5, "maxBatchSize: \t\t%d", config->maxBatchSize);
	mvprintw(12, column + 5, "activationFunction: \t\t%d", config->activationFunction);

	printActivationFunctions(column, config->activationFunction);
	
}

void printActivationFunctions(int column, int activationFunction)
{
	// mvprintw(13, column, "Activation functions: ");
	mvprintw(13, column + 5, "[%c] Relu", activationFunction & 0x0001 ? 'x' : ' ');
	mvprintw(14, column + 5, "[%c] Selu", activationFunction & 0x0002 ? 'x' : ' ');
	mvprintw(15, column + 5, "[%c] Elu", activationFunction & 0x0004 ? 'x' : ' ');
	mvprintw(16, column + 5, "[%c] Celu", activationFunction & 0x0008? 'x' : ' ');
	mvprintw(17, column + 5, "[%c] Glu", activationFunction & 0x0010 ? 'x' : ' ');
	mvprintw(18, column + 5, "[%c] Gelu", activationFunction & 0x0020 ? 'x' : ' ');
	mvprintw(19, column + 5, "[%c] Sigmoid", activationFunction & 0x0040 ? 'x' : ' ');
	mvprintw(20, column + 5, "[%c] Softmax", activationFunction & 0x0080 ? 'x' : ' ');
	mvprintw(21, column + 5, "[%c] Softplus", activationFunction & 0x0100 ? 'x' : ' ');
	mvprintw(22, column + 5, "[%c] Softsign", activationFunction & 0x0200 ? 'x' : ' ');
	mvprintw(23, column + 5, "[%c] Tanh", activationFunction & 0x0400 ? 'x' : ' ');
	mvprintw(24, column + 5, "[%c] Exponential", activationFunction & 0x0800 ? 'x' : ' ');
	mvprintw(25, column + 5, "[%c] Linear", activationFunction & 0x1000 ? 'x' : ' ');
	mvprintw(26, column + 5, "[%c] LogSigmoid", activationFunction & 0x2000 ? 'x' : ' ');
	
}