#pragma once

#include  "CVector/CVector.h"
#include <string.h>


#ifndef SHELLHANDLER_H
#define SHELLHANDLER_H
 
struct Command_s
{
	char command[48];
	int(*func)(CVectorString);
};
typedef struct Command_s Command;

typedef struct CVectorCommand_s
{
	int size;
	int capacity;
	Command * data;

} CVectorCommand;





enum StateCodes
{
	exitState,
	runState,
	restartState
};


int CommandIsGreater(Command lhs , Command rhs);
int CommandComparator(char* val ,Command cmd );



void ShellAddCommand(const char* cmdStr ,int (*func)(CVectorString));
void ShellAddCommandLoop(const char* cmdStr ,int (*func)(CVectorString));
void InitInlineShell();
int RunConsoleQuery();



#endif
