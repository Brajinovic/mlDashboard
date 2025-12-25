#include "nnetwork.h"



void createNetwork(char* name, struct n_network* network)
{
	network->name = (char*)calloc(sizeof(char), MAX_MENU_ITEM_SIZE);
	memcpy(network->name, name, MAX_MENU_ITEM_SIZE);
}


void deleteNetwork(int index);

void addLayer(struct n_network* network)
{
	// add new node to the linked list
	// display it --- it's info on the screen

	int index;
	echo();
  	curs_set(1); // hide cursor


	mvprintw(3, 2, " Enter the new layer index: ");
	scanw(" %d ", &index);


	mvprintw(4, 2, " Enter the layer index: %d", index);

	noecho();
    curs_set(0);
	
    // think I am getting sidetracked. I want to give available ranges and then the python script should create permutations from those ranges... This means there is no need to create the whole network, I don't need this submenu at all...

	getch();
}


void removeLayer(struct n_network* network)
{
	int index;
	echo();
  	curs_set(1); // hide cursor


	mvprintw(3, 2, " Enter the layer index: ");
	scanw("%d", &index);


	mvprintw(4, 2, " Enter the layer index: ");

	noecho();
    curs_set(0);
	
	getch();
}




void printNetwork(struct n_network* network, int row, int col)
{
	mvprintw(((row - 10) / 2), (col - MAX_MENU_ITEM_SIZE*2) / 2, "Network name: %s ", network->name);
	mvprintw(((row - 10) / 2) + 1, (col - MAX_MENU_ITEM_SIZE*2) / 2, "Layer 0: VGG16(weights=\"imagenet\", include_top=False, input_shape=(IMAGE_SIZE, IMAGE_SIZE, 3), pooling=\"avg\") ");
	mvprintw(((row - 10) / 2) + 2, (col - MAX_MENU_ITEM_SIZE*2) / 2, "Layer 1: modelB.add(Flatten()) ");
	// mvprintw(((row - 10) / 2), (col - MAX_MENU_ITEM_SIZE) / 2, "Network name: %s ", network->name);
	// now I can use a for loop to print the layers...
	mvprintw(((row - 10) / 2) + 4, (col - MAX_MENU_ITEM_SIZE*2) / 2, "Layer 3: modelB.add(Dense(4, activation=\"sigmoid\")) ");
	

}

