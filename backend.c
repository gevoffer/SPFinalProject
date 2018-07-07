/*
 * backend.c
 *
 *  Created on: Jul 1, 2018
 *      Author: Gev Offer
 */

#include "backend.h"

gameCell* create_cell() {
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

moveListNode* create_node(moveListNode* prevNode, moveListNode* nextNode, int prevValue, int setValue, int row, int col){
	moveListNode* node = (moveListNode*)malloc(sizeof(moveListNode*));
	if(node == NULL){
		return NULL;
	}
	node->prevMove = prevNode;
	node->nextMove = nextNode;
	node->prevValue = prevValue;
	node->setValue = setValue;
	node->row = row;
	node->col = col;
	return node;
}

Game* create_game(){
	Game* game = (Game*)malloc(sizeof(Game*));
	if(game == NULL){
		return NULL;
	}
	game->board = create_board();
	game->mode = INIT;
	game->markErrors = false;
	game->lastMove = create_node(NULL, NULL, -1, -1, -1 ,-1);
	return game;
}

void printSepRow() {
	int i;
	for (i=0 ; i < 4*BLOCK_ROW_SIZE*BLOCK_COL_SIZE*BLOCK_COL_SIZE+1 ; i++ ) {
		printf("-");
	}
	printf("\n");
}

void printRow(int rowNum, gameBoard* board, Game* game) {
	int i;
	for (i = 0 ; i < BLOCK_ROW_SIZE*BLOCK_COL_SIZE ; i++){
		if (i%BLOCK_COL_SIZE==0) {
			printf("|");
		}
		printCell(board->boardCells[i][rowNum], game);
	}
	printf("|\n");
}

void printCell(gameCell* cell, Game* game) {
	if (cell->value != 0) {printf (" %2d",cell->value);}
	else {printf("   ");}
	if (cell->fixed) {printf(".");}
	else if ((cell->erroneous) || game->markErrors ){printf("*");}
	else {printf(" ");}
}

void printBoard(gameBoard* board, Game* game) {
	int i;
	for (i=0 ; i < BLOCK_ROW_SIZE*BLOCK_COL_SIZE ; i++) {
		if (i%BLOCK_COL_SIZE==0) {
			printSepRow();
		}
		printRow(i, board, game);
	}
	printSepRow();
}
