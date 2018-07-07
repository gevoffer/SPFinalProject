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
	bool fixed;
	bool erroneous;
} gameCell;

typedef struct block{
	gameCell blockCells[BLOCK_ROW_SIZE][BLOCK_COL_SIZE];
	int boardRow;
	int boardCol;
} gameBlock;

typedef struct board{
	gameCell* boardCells[BLOCK_ROW_SIZE * BLOCK_COL_SIZE][BLOCK_ROW_SIZE * BLOCK_COL_SIZE];
} gameBoard;

typedef struct game{
	gameBoard* board;
	MODE mode;
	moveNode* lastMove;
};

typedef struct movenode{
	moveNode* nextMove;
	moveNode* prevMove;
	int row;
	int col;
	int prevValue;
	int setValue;
} moveNode;

typedef struct command{
	GAME_COMMAND cmd;
	int vars[3];
} command;


#endif /* BACKEND_H_ */
