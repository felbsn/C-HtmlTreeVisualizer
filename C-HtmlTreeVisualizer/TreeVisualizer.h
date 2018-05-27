#ifndef TreeVisualizer_H
#define TreeVisualizer_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CVector/CVector.h"


int PackageTree(bNode* root ,const char* outputFile ,void (*func)( FILE*,void*));

void PrintTreeInOrder(bNode* root , void (*functor)(void*));

//int greaterPrinter(bNode* root , int value);

void PrintTreeGreater(bNode* root, int value, void(*functor)(void*));





#endif