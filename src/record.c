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

    fptr = fopen("file.txt", "ab");

    if (fptr == NULL) 
        printf("The file is not opened.");
    else
    {
    	parameters->id = time(0);
    	parameters->activationFunction = parameters->activationFunction > 0 ? parameters->activationFunction : 1;
    	parameters->minLayerCount = parameters->minLayerCount > 0 ? parameters->minLayerCount : 2;
    	parameters->maxLayerCount = parameters->maxLayerCount > 0 ? parameters->maxLayerCount : 8;
    	parameters->minNeuronCount = parameters->minNeuronCount > 0 ? parameters->minNeuronCount : 16;
    	parameters->maxNeuronCount = parameters->maxNeuronCount > 0 ? parameters->maxNeuronCount : 128;
    	parameters->minEpochSize = parameters->minEpochSize > 0 ? parameters->minEpochSize : 10;
    	parameters->maxEpochSize = parameters->maxEpochSize > 0 ? parameters->maxEpochSize : 1000;
    	parameters->minBatchSize = parameters->minBatchSize > 0 ? parameters->minBatchSize : 10;
    	parameters->maxBatchSize = parameters->maxBatchSize > 0 ? parameters->maxBatchSize : 100;
    	
    	fwrite(parameters, RECORD_OFFSET, 1, fptr);

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
    	fread(parameters, RECORD_OFFSET, 1, fptr);
    	// fclose(fptr);
    }
}


void printConfig(int column, struct learning_parameter_record* config)
{
	mvprintw(2, column, "Active config: ");
	mvprintw(3, column + 5, "ID: \t\t\t%ld", config->id);
	mvprintw(4, column + 5, "minLayerCount:  \t\t%hu", config->minLayerCount);
	mvprintw(5, column + 5, "maxLayerCount:  \t\t%hu", config->maxLayerCount);
	mvprintw(6, column + 5, "minNeuronCount: \t\t%hu", config->minNeuronCount);
	mvprintw(7, column + 5, "maxNeuronCount: \t\t%hu", config->maxNeuronCount);
	mvprintw(8, column + 5, "minEpochSize:  \t\t%hu", config->minEpochSize);
	mvprintw(9, column + 5, "maxEpochSize:  \t\t%hu", config->maxEpochSize);
	mvprintw(10, column + 5, "minBatchSize: \t\t%hu", config->minBatchSize);
	mvprintw(11, column + 5, "maxBatchSize: \t\t%hu", config->maxBatchSize);
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

void fillList(FILE* fptr, struct menu_template* config_list)
{

	struct menu_item* item;
	uint64_t id;
	struct learning_parameter_record param;
	char str[20];
	
	config_list->cursor_index = 0;
	config_list->num_of_items = 0;
	config_list->items = NULL;
	// in order to use the already written code and work around the fact that I don't know how many configs i.e. menu items there are going to be, I can allocate some memory in the beginning, and free it and reallocate if I need more of it. It is a really stupid and inefficient idea, but I am not paid to implement a linked list. Mby in the future :)
	fseek(fptr, 0, SEEK_SET);
	while(fread(&param, RECORD_OFFSET, 1, fptr))
	{
		config_list->num_of_items++;
		
        struct menu_item **tmp = realloc(
            config_list->items,
            config_list->num_of_items * sizeof *config_list->items
        );

        if (!tmp) {
            perror("realloc");
            exit(1);
        }

        config_list->items = tmp;

        struct menu_item* item = calloc(1, sizeof *item);

        snprintf(str, sizeof str, "%ld", param.id);

        createItem(str, NULL, NULL, NULL, item);

        config_list->items[config_list->num_of_items - 1] = item;


		fseek(fptr, config_list->num_of_items * RECORD_OFFSET, SEEK_SET);


	}

}
