#pragma warning(disable:4996)
#include "UserData.h"



void UserDataPrinter(FILE* fo , void* data)
{
	UserData* ud = (UserData*)data;
	fprintf(fo, "%s", ud->name);
    int i;
	for ( i = 0; i < ud->friendList.size; ++i)
	{
		fprintf(fo, ",%d", ud->friendList.data[i]);
	}

}

UserData* newUserData(const char* name)
{
	UserData* ud = (UserData*) malloc(sizeof(UserData));

	int strSize = strlen(name)+1 ;
	strSize = (strSize > MaxUserNameSize) ? MaxUserNameSize : strSize;

	strncpy(ud->name , name , strSize);
	ud->name[strSize] = '\0';

	VectorInit(ud->friendList);

	return ud;
}

void* newUserDataGeneric()
{
	UserData* ud = (UserData*) malloc(sizeof(UserData));
	strcpy(ud->name , "Node" );
	VectorInit(ud->friendList);
	return ud;
}

void UserAssingList(UserData* ud, const int* friendList ,int friendCount)
{
	if(friendList)
	{
	VectorResize(ud->friendList , friendCount);
	memcpy(ud->friendList.data , friendList , sizeof(int)*friendCount);
	}
}

void UserChangeName(UserData* ud , const char* name)
{
	int strSize = strlen(name)+1 ;
	strSize = (strSize > MaxUserNameSize) ? MaxUserNameSize : strSize;

	strncpy(ud->name , name , strSize);
	ud->name[strSize] = '\0';
}

void UserAddFriend(UserData* ud, int friendID)
{
	 VectorAppend(ud->friendList , friendID);
}
void UserRemoveFriend(UserData* ud, int friendID)
{
	 VectorDelete(ud->friendList , friendID);
 }


void printUserData(UserData* ud)
{
	printf("UserName: %s , friends: ",ud->name );
	if(ud->friendList.size > 0)
	{
		int i;
		for ( i = 0; i < ud->friendList.size; ++i)
		{
		    printf("%4d ", ud->friendList.data[i]);
		}

	}else
	{
     	printf("%s", " empty* ");
	}
	printf("\n");
}

void *newUserDataStrtok()
{
	UserData* ud;
	char* delim = 0;

	delim = strtok(NULL , ",-");
	if(delim)
	{
		ud = newUserData(delim);
		while(delim = strtok(NULL , ",- "))
		{
			VectorAppend(ud->friendList , atoi(delim));
		}
	}
	else
	{
		ud = newUserData("node");
	}
	return ud;
}
