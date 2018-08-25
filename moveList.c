/*
 * moveList.c
 *
 *  Created on: Aug 25, 2018
 *      Author: Gev Offer
 */
#include "moveList.h"

moveNode* head;
moveNode* tail;

void initialize_moveList(){
	head = NULL;
	tail = NULL;
}
moveNode* create_node(int moves[], int num_of_moves){

	struct moveListNode* node = (struct moveListNode*)malloc(sizeof(struct moveListNode) + num_of_moves);
	if(node == NULL){
		return NULL;
	}
	node->prevMove = NULL;
	node->nextMove = NULL;
	int i;
	for(i = 0; i < num_of_moves; i++){
		node->moves[4*i] = moves[4*i];
		node->moves[4*i + 1] = moves[4*i + 1];
		node->moves[4*i + 2] = moves[4*i + 2];
		node->moves[4*i + 3] = moves[4*i + 3];
	}
	return node;
}

void add_moveList_node(int moves[], int num_of_moves){
	struct moveListNode* newNode = create_node(moves, num_of_moves);
	struct moveListNode* temp;
	temp = head;

	if(head == NULL){
		head = newNode;
		tail = newNode;
		return;
	}
	else{
		while (temp->nextMove != NULL){
			temp = temp->nextMove;
		}
		temp->nextMove = newNode;
		newNode->prevMove = temp;
		tail = newNode;
	}
}
/*
 * destroys nodes from the current one and on. make sure to provide as input
 * the node following the one you're at
 */
void destroy_moveList_forwards(moveNode* node){
	moveNode* prev;
	if(node->nextMove != NULL){
		destroy_moveList_forwards(node->nextMove);
	}
	//prev = node->prevMove;
	free(node);
	//prev->nextMove=NULL;
}

void destroy_moveList_backwards(moveNode* node){
	moveNode* prev;
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

struct moveListNode* get_moveList_head(){
	return head;
}

struct moveListNode* get_moveList_tail(){
	return tail;
}
