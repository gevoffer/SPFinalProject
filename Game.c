/*
 * Game.c
 *
 *  Created on: Aug 25, 2018
 *      Author: inbar
 */

#include "Game.h"
#include "backend.h"

Game* game;
gameBoard* game_board;
gameBoard* solution_board;
//int num_of_blanks;


//TODO- works only in edit and solve mode. When in init- treat as invalid command (see instructions)
//TODO- if value is set change moveslist accordingly.
void user_set_cell(int x, int y, int value){
	gameCell* cell;
	int prevVal;

	cell = get_cell_from_coordinates(game_board, x, y);
	prevVal = cell->value;

	if (x<1 || x> GAME_SIZE || y<1 || y>GAME_SIZE || value<0 || value >GAME_SIZE) {
		printf("Error: value not in range 0-%d\n", GAME_SIZE);
	}
	else if (cell->fixed == 1) {
		printf("Error: cell is fixed\n");
	}
	else {
		cell->value = value;
		if (cell->possibleVals[value]==0) {
			cell->erroneous = 1;
		}
		cell->possibleVals[value]=0;
		update_neighbours(game_board, cell, prevVal);
	}
	return;
}

