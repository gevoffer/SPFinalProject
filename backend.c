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

/*
 * destroys nodes from the current one and on. make sure to provide as input
 * the node following the one you're at
 */
void destroy_moveList_forwards(moveListNode* node){
	moveListNode* prev;
	if(node->nextMove != NULL){
		destroy_moveList_forwards(node->nextMove);
	}
	//prev = node->prevMove;
	free(node);
	//prev->nextMove=NULL;
}

void destroy_moveList_backwards(moveListNode* node){
	moveListNode* prev;
	if (node->nextMove != NULL){
		destroy_moveList_forwards(node->nextMove);
	}
	if(node->prevMove == NULL){
		free(node);
		return;
	}
	prev = node->prevMove;
	free(node);
	//prev->nextMove=NULL;
	destroy_moveList_backwards(prev);
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

void destroy_game(Game* game){
	destroy_board(game->board);
	destroy_moveList_backwards(game->lastMove);
	free(game);
}

void printSepRow() {
	int i;
	for (i=0 ; i < 4*BLOCK_ROW_SIZE*BLOCK_COL_SIZE+BLOCK_COL_SIZE+1 ; i++ ) {
		printf("-");
	}
	printf("\n");
}

//void printRow(int rowNum, Game* game) {
void printRow(int rowNum, gameBoard* board) {
	int i;
	gameCell* tmpCell;
	for (i = 0 ; i < BLOCK_ROW_SIZE*BLOCK_COL_SIZE ; i++){
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
	for (i=0 ; i < BLOCK_ROW_SIZE*BLOCK_COL_SIZE ; i++) {
		if (i%BLOCK_COL_SIZE==0) {
			printSepRow();
		}
		printRow(i, board);
	}
	printSepRow();
}
