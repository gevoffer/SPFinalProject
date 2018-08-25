/*
 * moveList.h
 *
 *  Created on: Aug 25, 2018
 *      Author: Gev Offer
 */

#ifndef MOVELIST_H_
#define MOVELIST_H_

#include "backend.h"

void initialize_moveList();

moveNode* create_node(int moves[], int num_of_moves);

void destroy_moveList_forwards(moveNode* node);

void destroy_moveList_backwards(moveNode* node);

#endif /* MOVELIST_H_ */
