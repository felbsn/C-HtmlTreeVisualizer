#ifndef NodeAlgorithm_H
#define NodeAlgorithm_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "DataTypes.h"
#include "TreeVisualizer.h"
#include "CVector/CVector.h"

#define TREE_BALANCE_TOLERANCE 1



/* basic funtion definitions */

bNode * newNode();
bNode * newNodeValue(int value);
 
void NodeAssignData(bNode* node ,void* data);

int ReadTreeArrayFrom(const char* filePath ,bNode** root, void* (*functor)());

bNode* FindNode(bNode* root , int value);

int DeleteNode(bNode** root , int value);
void InsertNode(bNode** root , bNode* node);


void freeNodeChain(bNode** root);

int TreeElementCount(bNode* root );
int TreeDepth(bNode* root );


void TreeBalance(bNode** root);
void BalanceNodes(bNode** root);

void InsertRawLeft(bNode* parent , bNode* node);
void InsertRawRight(bNode* parent , bNode* node);


/*functor definitions*/
int NodeGreater(bNode* lhs , bNode* rhs);
int NodeLower(bNode* lhs , bNode* rhs);


#endif