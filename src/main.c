#include <stdio.h>
#include <ncurses.h>
#include <string.h>

#include "hello.h"
#include "menu.h"
#include "record.h"
#include "const.h"
#include "callback.h"


struct menu_template main_menu;
struct menu_template results_menu;
struct learning_parameter_record active_config;


// global variables
int exit_loop = 0;
int level_up = 0;

int row = 0;
int col = 0;

int main(int argc, char** argv)
{
	// screen dimension variables 
	

	int active_menu_index = 0;
	struct menu_template* active_menu = &main_menu;
  
  // key input variable
  int input = 0;

  int cursor_index = 0;
    
  int num_of_items = 0;

  initscr();				/* Start curses mode */
  
  getmaxyx(stdscr,row,col);
  noecho();
  curs_set(0); // hide cursor
  
  fillMenu(&main_menu, 
  				 NULL,	// parent menu

  				 (struct menu_template*[]) {	// child menu
  				 									NULL, 
  													&results_menu,
  													NULL,
  													NULL,
  													NULL},
  				 (void (*[])(void)){ 					// callback function pointers
 													&callbackStartLearning,
 													NULL,
 													&callbackBrowseConfigs,
 													&callbackNewNetworkScratch,
 													&callbackExit},

  				 (char[][50]) {
													"Start learning\0",
													"Show results\0",
													"Browse configs\0",
													"Create new config\0",
													"Exit\0"}, 
	 												NUM_OF_ITEMS_MAIN_MENU);

  
  fillMenu(&results_menu, 
  				 &main_menu,
  				 (struct menu_template*[]){	// child
  				 												 NULL, 
  																 NULL,
  																 NULL,
  																 NULL},
  				 (void (*[])(void)){ 				// callback function pointers
  				 												 NULL,
  				 												 NULL,
  				 												 NULL,
  				 												 &callbackLevelUp},
  				 	(char[][50]) {
																	 "Show last results\0",
																	 "Show best model\0",
																	 "Show last 10 results\0",
																	 "Back\0"}, 
																	 NUM_OF_ITEMS_RESULTS_MENU);




  // main_menu.items[1]->child_menu = &results_menu;

  num_of_items = active_menu->num_of_items;
  printMenu(active_menu);

  while(1)
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
  			cursor_index = 0;
  		} else
  		{
  			mvprintw(0, 1, " No submenu! Checking for a callback function! \n\r");
  			if (active_menu->items[cursor_index]->callback != NULL)
  			{
  				mvprintw(1, 1, " There is a callback!\n\r ");
  				// do the callback function call
  				active_menu->items[cursor_index]->callback();

  			} else
  			{
  				mvprintw(1, 1, " Well fuck it, no submenu or callback! \n\r");
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
  		break;
  	
  	printMenu(active_menu);
  	
  	if (active_config.id != 0)
  		printConfig(2, &active_config);
  }

  endwin();                       	/* End curses mode */
  
  return 0;
}