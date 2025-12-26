#include "menu.h"



void getUserInput(char* name)
{
	echo();
  	curs_set(1); // hide cursor


	getstr(name);


	noecho();
    curs_set(0); // hide cursor
}


void createItem(char* name, 
				struct menu_template* parent, 
				struct menu_template* child, 
				void (*callback)(),
				struct menu_item* item)
{
	item->name = (char*)calloc(sizeof(char), MAX_MENU_ITEM_SIZE);
	// copy the name value from stack to heap
	// *((*item).name) = *name;
	memcpy(item->name, name, MAX_MENU_ITEM_SIZE);
	// store the pointers
	item->parent_menu = parent;
	item->child_menu = child;
	item->callback = callback;
}


void fillMenu(struct menu_template* menu,
			  struct menu_template* parent_menu,
			  struct menu_template** child_menus,
			  void (*callback_functions[])(), 
			  char item_names[][50], 
			  int num_of_items)
{
	struct menu_item* item;
	
	menu->cursor_index = 0;
	menu->num_of_items = num_of_items;
	menu->items = (struct menu_item**)calloc(sizeof(struct menu_item*), (*menu).num_of_items);

	for (int i = 0; i < menu->num_of_items; i++)
	{
		// allocate the memory for an item and fill it out
		item = (struct menu_item*)calloc(sizeof(struct menu_item), 1);
		createItem(item_names[i],
				   parent_menu,
				   child_menus[i],
				   callback_functions[i],
				   item);
		// the menu.items is an array of pointers to the menu_item 
		// I need to add the address of each item to that array
		menu->items[i] = item;
		if (i == 0)	mvprintw(2, 1, " %s hihi\n\r", menu->items[i]->name);
	}
}



void printMenu(struct menu_template* menu)
{	
	clear();

	for( int i = 0; i < menu->num_of_items; i++)
	{

		if (menu->cursor_index == i) attron(A_STANDOUT);
  		
  		mvprintw(((row - menu->num_of_items) / 2) + i, 
  				 (col - MAX_MENU_ITEM_SIZE) / 2, 
  				 " %s ", 
  				 menu->items[i]->name);
  				// "Majmun\0");
  		if ((*menu).cursor_index == i) attroff(A_STANDOUT);
  	
	}
}
	


void printSelectedActivationFunctions(struct menu_template* menu)
{
	// flag I use to only print the "selected activation functions" text once...
	
	int once = 0;
	
	for (int i = 0; i < menu->num_of_items; i++)
	{
		if (menu->items[i]->name[1] == 'x')
		{
			if (once == 0)
			{
				mvprintw(2, col - MAX_MENU_ITEM_SIZE - 2, "Selected activation functions: ");
				once = 1;
			}

			mvprintw(3 + i, col - MAX_MENU_ITEM_SIZE - 2, "%s", menu->items[i]->name);
		}
	}
}

void userInput(char* display_text, char* input)
{
	clear();
	mvprintw((row / 2), 
  			 (col - MAX_MENU_ITEM_SIZE) / 2, 
  			 " %s ", 
  			 display_text);
	getUserInput(input);
}


void fillList(FILE* fptr, struct menu_template* config_list)
{

	struct menu_item* item;
	long int id;
	char str[20];
	
	config_list->cursor_index = 0;
	config_list->num_of_items = 0;
	config_list->items = NULL;
	// in order to use the already written code and work around the fact that I don't know how many configs i.e. menu items there are going to be, I can allocate some memory in the beginning, and free it and reallocate if I need more of it. It is a really stupid and inefficient idea, but I am not paid to implement a linked list. Mby in the future :)
	
	while(fscanf(fptr, "%*s %ld", &id) == 1)
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

        snprintf(str, sizeof str, "%ld", id);

        createItem(str, NULL, NULL, NULL, item);

        config_list->items[config_list->num_of_items - 1] = item;


		fseek(fptr, config_list->num_of_items * 218, SEEK_SET);


	}

}
