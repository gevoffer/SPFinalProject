/*
 * backend.h
 *
 *  Created on: Jul 1, 2018
 *      Author: Gev Offer
 */

#ifndef BACKEND_H_
#define BACKEND_H_

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <malloc.h>

#define BLOCK_ROW_SIZE 3
#define BLOCK_COL_SIZE 3

typedef enum{
	LOAD_SOLVE,
	LOAD_EDIT,
	SET_MARK_ERRORS,
	PRINT_BOARD,
	SET_CELL,
	HINT,
	VALIDATE,
	GENERATE,
	UNDO,
	REDO,
	SAVE,
	NUM_SOLUTIONS,
	AUTOFILL,
	RESTART,
	EXIT,
	INVALID
} GAME_COMMAND;

typedef enum{
	INIT,
	EDIT,
	SOLVE
} MODE;

typedef struct cell{
	int value;
	int row;
	int col;
	bool fixed;
	bool erroneous;
} gameCell;

typedef struct block{
	gameCell blockCells[BLOCK_ROW_SIZE][BLOCK_COL_SIZE];
	int boardRow;
	int boardCol;
} gameBlock;

typedef struct board{
	gameCell*** boardCells;
} gameBoard;

typedef struct moveListNode{
	struct moveListNode *nextMove;
	struct moveListNode *prevMove;
	int row;
	int col;
	int prevValue;
	int setValue;
}moveListNode;

typedef struct game{
	gameBoard* board;
	MODE mode;
	moveListNode* lastMove;
	bool markErrors;
} Game;

typedef struct command{
	GAME_COMMAND cmd;
	int vars[3];
} command;

gameCell* create_cell();

gameCell* copy_cell(gameCell* cell);

void destroy_cell(gameCell* cell);

gameBoard* create_board();

gameBoard* copy_board(gameBoard* board);

void destroy_board(gameBoard* board);

moveListNode* create_node(moveListNode* prevNode, moveListNode* nextNode, int prevValue, int setValue, int row, int col);

void destroy_moveList_forwards(moveListNode* node);

void destroy_moveList_backwards(moveListNode* node);

Game* create_game();

void destroy_game(Game* game);

void printSepRow();

//void printRow(int rowNum, Game* game);
//
//void printCell(gameCell* cell, Game* game);
//
//void printBoard(Game* game);

void printRow(int rowNum, gameBoard* board);

void printCell(gameCell* cell, gameBoard* board);

void printBoard(gameBoard* board);

#endif /* BACKEND_H_ */
