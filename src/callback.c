#include "callback.h"


struct learning_parameter_record parameters;

void callbackStartLearning(void)
{
	// what to do? Start the python script that will load the config from file...
	exit_loop = 1;
}


void callbackNewNetworkScratch(void)
{
	struct menu_template network_config_menu;
	struct menu_template activation_function_menu;

	fillMenu( &network_config_menu, 
    	   	  NULL, // parent menu

			  (struct menu_template*[]){	// child menu
										NULL, 
										NULL, 
									 	NULL, 
									 	NULL, 
									 	NULL, 
									 	NULL,
									 	NULL,
									 	NULL,
									 	NULL,
									 	NULL,
									 	&activation_function_menu,
									 	NULL,
									},
			  (void (*[])(void)){ 				// callback function pointers
								 NULL,
								 NULL,
								 &callbackMinNoHiddenLayers,
								 &callbackMaxNoHiddenLayers,
								 &callbackMinNumberNeurons,
								 &callbackMaxNumberNeurons, 
								 &callbackMinEpochSize,
								 &callbackMaxEpochSize, 
								 &callbackMinBatchSize,
								 &callbackMaxBatchSize,  
								 NULL, 
			 					 &callbackExit,
			 					}, 
			  (char[][50]) {
							 "Model:                 Sequential (default)\0",
							 "Application:           VGG16 (default)\0",
							 "Min layer count:       2 (default)\0",
							 "Max layer count:       8 (default)\0",
							 "Min neuron count:      16 (default)\0",
							 "Max neuron count:      128 (default)\0",
							 "Min epoch size:        100 (default)\0",
							 "Max epoch size:        1000 (default)\0",
							 "Min batch size:        10 (default)\0",
							 "Max batch size:        100 (default)\0",
							 "Activation function/s: Relu (default)\0",
							 "Back\0",
							}, 
									 NUM_OF_ITEMS_CONFIG_MENU);

	fillMenu( &activation_function_menu, 
    	   	  &network_config_menu, // parent menu

			  (struct menu_template*[]){	// child menu 
									 	NULL, 
									 	NULL, 
									 	NULL, 
									 	NULL,
									 	NULL,
									 	NULL,
									 	NULL,			
									 	NULL,
									 	NULL,
									 	NULL, 
									 	NULL,
									 	NULL, 
									 	NULL,
									 	NULL, 
									 	NULL,
									},
			  (void (*[])(void)){ 				// callback function pointers
								 &callbackRelu,
								 &callbackSelu,
								 &callbackElu, 
								 &callbackCelu,
								 &callbackGlu, 
								 &callbackGelu,
								 &callbackSigmoid, 
								 &callbackSoftmax,
								 &callbackSoftplus,
								 &callbackSoftSign,
								 &callbackTanh,
								 &callbackExponential, 
								 &callbackLinear,
								 &callbackLogSigmoid, 
								 &callbackLevelUp,  
			 					 
			 					}, 
			  (char[][50]) {
							 "[ ] Relu\0",
							 "[ ] Selu\0",
							 "[ ] Elu\0",
							 "[ ] Celu\0",
							 "[ ] Glu\0",
							 "[ ] Gelu\0",
							 "[ ] Sigmoid\0",
							 "[ ] Softmax\0",
							 "[ ] Softplus\0",
							 "[ ] Softsign\0",
							 "[ ] Tanh\0",
							 "[ ] Exponential\0",
							 "[ ] Linear\0",
							 "[ ] LogSigmoid\0",
							 "Back\0",
							}, 
							 NUM_OF_ACTIVATION_FUNCTIONS);


	int active_menu_index = 0;
	struct menu_template* active_menu = &network_config_menu;
	  
	// key input variable
	int input = 0;
	
	int cursor_index = 0;
	  
	int num_of_items = active_menu->num_of_items;

	
	clear();
	printMenu(active_menu);
	printSelectedActivationFunctions(&activation_function_menu);
	  
	while (1)
	{
	  	refresh();
	  	input = getch();
	
	  	if (input == 66) // arrow key down
	  	{	
	  		cursor_index = ++cursor_index < num_of_items ? cursor_index++ : 0;
	  		active_menu->cursor_index = cursor_index;
	  		
	  	}
	  	else if (input == 65) // arrow key up
	  	{
		  	cursor_index = --cursor_index >= 0 ? cursor_index-- : num_of_items - 1;
		  	active_menu->cursor_index = cursor_index;

	  	}
	  	else if (input == 10) // enter
	  	{
	  		if (active_menu->items[cursor_index]->child_menu != NULL)
	  		{
	  			active_menu = active_menu->items[cursor_index]->child_menu;
	  			num_of_items = active_menu->num_of_items;
	  			cursor_index = active_menu->cursor_index;
	  		} else
	  		{
	  			mvprintw(0, 1, " No submenu! Checking for a callback function! \n\r");
	  			if (active_menu->items[cursor_index]->callback != NULL)
	  			{
	  				mvprintw(1, 1, " There is a callback!\n\r ");
	  				// do the callback function call
	  				active_menu->items[cursor_index]->callback();
	  				// if the 
	  				if (active_menu == &activation_function_menu && cursor_index != (num_of_items - 1))
	  					active_menu->items[cursor_index]->name[1] = active_menu->items[cursor_index]->name[1] == 'x' ? ' ' : 'x';

	  				// edit menu item names
	  				refreshMenu(&network_config_menu, &parameters);

	  			} else
	  			{
	  				mvprintw(1, 1, " Well, fuck it, no submenu or callback! \n\r");
	  			}
	  		}
		}
			
		if (level_up == 1)
		{
			active_menu = active_menu->items[cursor_index]->parent_menu;
			num_of_items = active_menu->num_of_items;
  			cursor_index = active_menu->cursor_index;
			level_up = 0;
		}

	  	if (input == 'q')
	  		exit_loop = 1;


	  	if (exit_loop == 1)
	  	{
	  		exit_loop = 0;
	  		writeConfig(&parameters);
	  		break;
	  	}

	  	printMenu(active_menu);
	  	printSelectedActivationFunctions(&activation_function_menu);
	}
	
}

/*
	Select the number of hidden layers that are allowed

	Given that this is a callback function I cannot return anything or pass an argument. How do I do this?

	What I can do is make a second loop that is going to abstract the data from the main loop. Given the callback functions are specific I can create the required menus inside of here...

*/

void callbackMinNoHiddenLayers(void)
{
	char* input = calloc(sizeof(char), MAX_MENU_ITEM_SIZE);
	userInput((char[50]){"Min No. of hidden layers: "}, input);
	parameters.minLayerCount = atoi(input);

}


void callbackMaxNoHiddenLayers(void)
{
	char* input = calloc(sizeof(char), MAX_MENU_ITEM_SIZE);
	userInput((char[50]){"Max No. of hidden layers: "}, input);
	parameters.maxLayerCount = atoi(input);

}



/*
	Set the min number of neurons allowed
*/
void callbackMinNumberNeurons(void)
{
	char* input = calloc(sizeof(char), MAX_MENU_ITEM_SIZE);
	userInput((char[50]){"Min No. of neurons: "}, input);
	parameters.minNeuronCount = atoi(input);
}

/*
	Set the max number of neurons allowed
*/
void callbackMaxNumberNeurons(void)
{
	char* input = calloc(sizeof(char), MAX_MENU_ITEM_SIZE);
	userInput((char[50]){"Max No. of neurons: "}, input);
	parameters.maxNeuronCount = atoi(input);
}



/*
Select the epoch size
*/
void callbackMinEpochSize(void)
{
	char* input = calloc(sizeof(char), MAX_MENU_ITEM_SIZE);
	userInput((char[50]){"Min epoch size: "}, input);
	parameters.minEpochSize = atoi(input);
}

void callbackMaxEpochSize(void)
{
	char* input = calloc(sizeof(char), MAX_MENU_ITEM_SIZE);
	userInput((char[50]){"Max epoch size: "}, input);
	parameters.maxEpochSize = atoi(input);
}


/*
Select the batch size
*/
void callbackMinBatchSize(void)
{
	char* input = calloc(sizeof(char), MAX_MENU_ITEM_SIZE);
	userInput((char[50]){"Min batch size: "}, input);
	parameters.minBatchSize = atoi(input);
}


void callbackMaxBatchSize(void)
{
	char* input = calloc(sizeof(char), MAX_MENU_ITEM_SIZE);
	userInput((char[50]){"Max batch size: "}, input);
	parameters.maxBatchSize = atoi(input);
}



void callbackActivationFunctions(void)
{
	exit_loop = 1;
}


void callbackNewNetworkTemplate(void)
{
	exit_loop = 1;
}

/*
level_up - flag indicating should the cursor
		   go up one level regarding the menu level
		   Active on 1
*/
void callbackLevelUp(void)
{
	level_up = 1;
}


/*
exit_loop - if set true, this flag indicates the program should 
			be terminated
			Active on 1
*/
void callbackExit(void)
{
	exit_loop = 1;
}


void callbackRelu(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0001;
}


void callbackSelu(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0002;
}


void callbackElu(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0004;
} 


void callbackCelu(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0008;
}


void callbackGlu(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x000F;
} 


void callbackGelu(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0010;
}


void callbackSigmoid(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0020;
} 


void callbackSoftmax(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0040;
}


void callbackSoftplus(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0080;
}


void callbackSoftSign(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x00F0;
}


void callbackTanh(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0100;
}


void callbackExponential(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0200;
} 


void callbackLinear(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0400;
}


void callbackLogSigmoid(void)
{
	parameters.activationFunction = parameters.activationFunction ^ 0x0800;
} 


