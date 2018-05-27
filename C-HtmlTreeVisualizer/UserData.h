#ifndef UserData_H
#define UserData_H

#include <stdio.h>
//#include "DataTypes.h"
#include "CVector/CVector.h"
#include <string.h>





#define MaxUserNameSize  32


struct UserData_s
{
	char name[32];
	CVectorInt friendList;
};
typedef struct  UserData_s UserData;



UserData* newUserData(const char* name);


void UserAssingList(UserData* ud, const int* friendList ,int friendCount);
void UserAddFriend(UserData* ud, int friendID);
void UserRemoveFriend(UserData* ud, int friendID);
void UserChangeName(UserData* ud , const char* name);
void printUserData(UserData* ud);

/*functors*/
void UserDataPrinter(FILE* fo , void* data);
void* newUserDataGeneric();
void* newUserDataStrtok();


#endif