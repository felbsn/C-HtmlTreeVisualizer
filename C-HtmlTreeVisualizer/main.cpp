#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CVector/CVector.h"

 #include "UserData.h"
#include "ShellHandler.h"
#include "TreeVisualizer.h"
#include "NodeAlgorithm.h"




/*#include "DataTypes.h"


*/



bNode* root = NULL;
const char* dataPath;


int clearFunction(CVectorString args);

int addNodeFunction(CVectorString args);

int delnodeFunction(CVectorString args);

int printgreaterFunction(CVectorString args);

int printinorderFunction(CVectorString args);

int cleartreeFunction(CVectorString args);

int printtreeFunction(CVectorString args);

int printnodeFuncion(CVectorString args);

int editnodeFunction(CVectorString args);

int readtreefromFunction(CVectorString args);

int treedepthFunction(CVectorString args);

int treesizeFunction(CVectorString args);

int readtreefromexFunction(CVectorString args);

int main(int argc , char* argv[])
{


	if(argc == 2)
	{
		dataPath = argv[1];
		FILE *ftest = fopen(dataPath , "r");
		if(ftest == NULL)
		{
			printf("Can't open given path exiting...\n");
			exit(0);
		}else
		{
			fclose(ftest);
		}
	}
	else
	{
	printf("Usage: %s {dataPath}\n",argv[0] );
	exit(0);
	}

	dataPath = "HTML\\data.js";

	InitInlineShell();

	ShellAddCommand("addnode" , addNodeFunction);
	ShellAddCommand("delnode" , delnodeFunction);
	ShellAddCommand("cleartree" , cleartreeFunction);
	ShellAddCommand("printinorder" , printinorderFunction);
	ShellAddCommand("printgreater" , printgreaterFunction);
	ShellAddCommand("printnode" , printnodeFuncion);
	ShellAddCommand("readtreefrom" , readtreefromFunction);
	ShellAddCommand("treedepth" , treedepthFunction);
	ShellAddCommand("treesize" , treesizeFunction);
	ShellAddCommand("editnode" , editnodeFunction);
	ShellAddCommand("clear" , clearFunction);
	ShellAddCommand("readtreefromex" , readtreefromexFunction);

	ShellAddCommandLoop("printtree" , printtreeFunction);

	return RunConsoleQuery();

}


int treedepthFunction(CVectorString args)
{
	int res = TreeDepth(root);
	printf("=>Tree Depth %d\n",res );
	return 1;
}

int treesizeFunction(CVectorString args)
{
	int res =TreeElementCount(root);
	printf("=>Tree size %d\n",res );
	return 1;
}


int clearFunction(CVectorString args)
{

#ifdef __linux__
    system("clear");
#elif _WIN32
    system("cls");
#endif
	return 1;
}

int addNodeFunction(CVectorString args)
{
	if(args.size > 1)
	{

	UserData* usr = NULL;
	int value = atoi(args.data[1]);
	bNode* nodetmp = newNodeValue(value);

	if(args.size > 2)
	{
		char* name = args.data[2];
		while(*name != 0){
			if(*name == '_') *name = ' ';
			name++;
		}

		usr = newUserData(args.data[2]);

		int i;
		for (i = 3; i < args.size; ++i)
			{
				UserAddFriend(usr , atoi(args.data[i]));
			}

	}else
	{
     	 usr = newUserData("InsertedNode");
	}
	nodetmp->data = usr;

	printf("=> inserting node value: {%d} name:{%s}\n", value  , usr ? usr->name : " ");
	InsertNode(&root , nodetmp);
	}
	return 1;
}

int delnodeFunction(CVectorString args)
{
	if(args.size > 1)
	{

	int value = atoi(args.data[1]);
	if(DeleteNode(&root ,value))
		printf("=> node deleted succesfully\n");
	else
		printf("=> node not found\n");
	}
	return 1;
}


int printgreaterFunction(CVectorString args)
{
	if(args.size > 1)
	{
	int value = atoi(args.data[1]);
	printf("=>%s %d \n" ,"printing greater than",value);
	PrintTreeGreater(root , value , 0);
	}
	return 1;
}

int printinorderFunction(CVectorString args)
{
	printf("=>%s\n", "printing tree ascending order");
	PrintTreeInOrder(root ,  0);
	return 1;
}



int cleartreeFunction(CVectorString args)
{

	freeNodeChain(&root);
    printf("=>%s\n", "tree cleared");
	return 1;
}

int printtreeFunction(CVectorString args)
{
	PackageTree(root ,dataPath , UserDataPrinter);
	return 1;
}


int printnodeFuncion(CVectorString args)
{
	if(args.size > 1)
	{
		int value = atoi(args.data[1]);
		bNode* node = FindNode(root ,value);
		if(node)
		{
			UserData* ud = (UserData*)node->data;
			printUserData(ud);
			if(ud->friendList.size > 0) printf("userFriends:\n");
			int i;
			for (i = 0; i < ud->friendList.size; ++i)
			{
				node = FindNode(root ,ud->friendList.data[i]);
				printf("ID:%d, %s\n", ud->friendList.data[i]  ,node != NULL ?((UserData*)(node->data))->name : "?");
			}

		}else
		{
			printf("=> user not found\n");
		}



	}
	return 1;
}


int editnodeFunction(CVectorString args)
{
	if(args.size > 1)
	{
	int value = atoi(args.data[1]);

	bNode* found = FindNode(root  , value);
	if(found)
	{
		UserData* usr = (UserData*)found->data;

		if(args.size > 2)
		{

			UserChangeName(usr , args.data[2]);
			int i;
			for (i = 3; i < args.size; ++i)
			{
				if(args.data[i][0] == '!')
				{
					UserRemoveFriend(usr , atoi(args.data[i]+1));
				}
				else
				{
					UserAddFriend(usr , atoi(args.data[i]));
				}

			}

		}
		printUserData(usr);
	}else
	{
		printf("=>Node not found \n");
	}

	}

	return 1;
}

int readtreefromexFunction(CVectorString args)
{
	if(args.size > 1)
	{

		int result = ReadTreeArrayFrom(args.data[1] , &root ,newUserDataStrtok);
		if(result)
		{
				printf("=>Tree generated Succesfully\n");
		}else
		{
			    printf("=>Some error occurred  code:%d\n",result);
		}

	}
	return 1;
}

int readtreefromFunction(CVectorString args)
{
	if(args.size > 1)
	{

		int result = ReadTreeArrayFrom(args.data[1] , &root ,newUserDataGeneric);
		if(result)
		{
				printf("=>Tree generated Succesfully\n");
		}else
		{
			    printf("=>Some error occurred  code:%d\n",result);
		}

	}
	return 1;
}

