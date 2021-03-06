/*
 * backend.c
 *
 *  Created on: Jul 1, 2018
 *      Author: Gev Offer
 */

#include "backend.h"

gameCell* create_cell() {
	int i;
	gameCell* cell = (gameCell*) malloc(sizeof(gameCell));
	if(cell == NULL) {
		free(cell);
		return NULL;
	}
	cell->value = 0;
	cell->row = -1;
	cell->col = -1;
	cell->fixed = false;
	cell->erroneous = false;
	for (i=0 ; i<GAME_SIZE ; i++) {
		cell->possibleVals[i]=i+1;
	}
	return cell;
}

gameCell* copy_cell(gameCell* cell){
	gameCell* new_cell = create_cell();

	new_cell->value = cell->value;
	new_cell->row = cell->row;
	new_cell->col = cell->col;
	new_cell->fixed = cell->fixed;
	new_cell->erroneous = cell->erroneous;

	return new_cell;
}

void destroy_cell(gameCell* cell) {
	if(cell == NULL){
		return;
	}
	free(cell);
}

gameBoard* create_board() {
	int i;
	int j;

	gameBoard* board = (gameBoard*)malloc(sizeof(gameBoard));
	if(board == NULL){
		free(board->boardCells);
		free(board);
		return NULL;
	}

	board->boardCells = calloc(BLOCK_ROW_SIZE * BLOCK_COL_SIZE, sizeof(gameCell**));
	for(i = 0; i < BLOCK_ROW_SIZE * BLOCK_COL_SIZE; i++){
		board->boardCells[i] = calloc(BLOCK_ROW_SIZE * BLOCK_COL_SIZE, sizeof(gameCell*));
		for(j = 0; j < BLOCK_ROW_SIZE * BLOCK_COL_SIZE; j++){
			board->boardCells[i][j] = create_cell();
			board->boardCells[i][j]->row = i;
			board->boardCells[i][j]->col = j;
		}
	}

	return board;
}

gameBoard* copy_board(gameBoard* board){
	int i;
	int j;

	gameBoard* new_board = create_board();
	for(i = 0; i < BLOCK_ROW_SIZE * BLOCK_COL_SIZE; i++){
		for(j = 0; j < BLOCK_ROW_SIZE * BLOCK_COL_SIZE; j++){
			new_board->boardCells[i][j] = copy_cell(board->boardCells[i][j]);
		}
	}

	return new_board;
}

void destroy_board(gameBoard* board){
	int i;
	int j;

	if(board == NULL){
		return;
	}

	for(i = 0; i < BLOCK_ROW_SIZE * BLOCK_COL_SIZE; i++){
		for(j = 0; j < BLOCK_ROW_SIZE * BLOCK_COL_SIZE; j++){
			destroy_cell(board->boardCells[i][j]);
		}
		free(board->boardCells[i]);
	}

	free(board->boardCells);
	free(board);
}



Game* create_game(){
	Game* game = (Game*)malloc(sizeof(Game*));
	if(game == NULL){
		return NULL;
	}
	game->board = create_board();
	game->mode = INIT;
	game->markErrors = false;
	//game->lastMove = create_node(NULL, NULL, -1, -1, -1 ,-1);
	return game;
}

void destroy_game(Game* game){
	destroy_board(game->board);
	//destroy_moveList_backwards(game->lastMove);
	free(game);
}

void printSepRow() {
	int i;
	for (i=0 ; i < 4*GAME_SIZE+BLOCK_COL_SIZE+1 ; i++ ) {
		printf("-");
	}
	printf("\n");
}

//void printRow(int rowNum, Game* game) {
void printRow(int rowNum, gameBoard* board) {
	int i;
	gameCell* tmpCell;
	for (i = 0 ; i < GAME_SIZE ; i++){
		if (i%BLOCK_COL_SIZE==0) {
			printf("|");
		}
//		tmpCell = game->board->boardCells[i][rowNum];
		tmpCell = board->boardCells[i][rowNum];
		printCell(tmpCell, board);
	}
	printf("|\n");
}

//void printCell(gameCell* cell, Game* game) {
void printCell(gameCell* cell, gameBoard* board) {
	if (cell->value != 0) {printf (" %2d",cell->value);}
	else {printf("   ");}
	if (cell->fixed) {printf(".");}
//	else if ((cell->erroneous) || game->markErrors ){printf("*");}
	else if (cell->erroneous){printf("*");}
	else {printf(" ");}
}

//void printBoard(Game* game) {
void printBoard(gameBoard* board) {
	int i;
	for (i=0 ; i < GAME_SIZE ; i++) {
		if (i%BLOCK_ROW_SIZE==0) {
			printSepRow();
		}
		printRow(i, board);
	}
	printSepRow();
}

gameCell* get_cell_from_coordinates(gameBoard* board, int x, int y){
	gameCell* cell;
	cell = board->boardCells[y-1][x-1];
	return cell;
}

void update_neighbours(gameBoard board, gameCell cell, int prevVal){
	int cellVal;
	int i;

	cellVal = cell->value;
	if (cellVal == 0) {
		// check if prevVal is valid for all neighbors
		for (i = 0 ; i < GAME_SIZE ; i++){
			if (check_if_possible(board, board->boardCells[cell->row][i], prevVal)) {
				board->boardCells[cell->row][i]->possibleVals[prevVal] = prevVal;
			}
			if (check_if_possible(board, board->boardCells[i][cell->col], prevVal)) {
				board->boardCells[i][cell->col]->possibleVals[prevVal] = prevVal;
			}
			// do the same with the whole block
		}
	}
	else if(cellVal != 0) {
		// remove cellVal from possible values list of all neighbors
		for (i = 0 ; i < GAME_SIZE ; i++){
			board->boardCells[cell->row][i]->possibleVals[cellVal]=0;
			board->boardCells[i][cell->col]->possibleVals[cellVal]=0;
			// do the same with the whole block
		}
	}
	return;
}

bool check_if_possible(gameBoard board, gameCell cell, int prevVal){
	int i;
	//compare to all in row- return 0 if error
	for (i=0 ; i<GAME_SIZE ; i++) {
		if (board->boardCells[cell->row][i]->value==prevVal) {
			return 0;
		}
	}
	//compare to all in column- return 0 if error
	for (i=0 ; i<GAME_SIZE ; i++) {
		if (board->boardCells[i][cell->col]->value==prevVal) {
			return 0;
		}
	}
	//TODO- compare to all in block- return 0 if error
	return true;
}
