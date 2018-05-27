

#include  "ShellHandler.h"

#pragma warning(disable:4996)

static CVectorCommand commands;
static CVectorCommand loopCmds;
static CVectorString eventStrings;


/* build in commands */
int  exitFunctor(CVectorString vec)
{
	printf("\nbye\n");

	//to do working enum system
	//...
	exit(0);
	return 0;
}

int clearFunctor(CVectorString args)
{

#ifdef __linux__
	system("clear");
#elif _WIN32
	system("cls");
#endif
	return 1;
}

int aboutFunctor(CVectorString args)
{
    printf("=> felbsn 2018 \n  Writed in c ....\n");

    return 1;
}

int helpFunctor(CVectorString vec)
{
	printf("there is %d functions...\n", commands.size );
	int i;
	for (i = 0; i < commands.size; ++i)
	{
	    Command* dat = (Command*)commands.data;
		printf("=> %s\n", dat[i].command ) ;
	}
	return 0;
}

int demoFunctor(CVectorString vec)
{
	printf("%s\n", "this is demo functor");
	int i;
	for (i = 0; i < vec.size; i++)
	{
		printf(" %s",vec.data[i]);
	}
	printf("\n");
	return 0;
}


int CommandIsGreater(Command lhs , Command rhs)
{
	char* ls = lhs.command;
	char* rs = rhs.command;

	while( (*ls && *rs) &&  *ls == *rs)
	{
		ls++;
		rs++;
	}

	if(*ls >= *rs)
		return 1;
	else
		return 0;
}

int CommandComparator(char* val ,Command cmd )
{
	return strcmp(val , cmd.command);
}



void ShellAddCommand(const char* cmdStr ,int (*func)(CVectorString))
{
	Command tmp;
	strcpy(tmp.command , cmdStr);
	tmp.func = func;
	VectorAppend(commands , tmp);
	VectorSort(commands ,CommandIsGreater );

}

void ShellAddCommandLoop(const char* cmdStr ,int (*func)(CVectorString))
{
	Command tmp;
	strcpy(tmp.command , cmdStr);
	tmp.func = func;

	VectorAppend(commands , tmp);
	VectorSort(commands ,CommandIsGreater );

	VectorAppend(loopCmds , tmp);
	VectorSort(loopCmds ,CommandIsGreater );
}

void InitInlineShell()
{
	VectorInit(commands);
	VectorInit(loopCmds);
	VectorInit(eventStrings);

	Command tmp;

	strcpy(tmp.command , "exit");
	tmp.func =exitFunctor;
	VectorAppend(commands , tmp);

	strcpy(tmp.command , "help");
	tmp.func =helpFunctor;
	VectorAppend(commands , tmp);

	strcpy(tmp.command , "demo");
	tmp.func =demoFunctor;
	VectorAppend(commands , tmp);

	strcpy(tmp.command, "clear");
	tmp.func = clearFunctor;
	VectorAppend(commands, tmp);

	strcpy(tmp.command, "about");
	tmp.func = aboutFunctor;
	VectorAppend(commands, tmp);

	VectorSort(commands ,CommandIsGreater );


}


int RunLoopCmds()
{	int i;
	for ( i= 0; i < loopCmds.size; ++i)
	{
		int result = loopCmds.data[i].func(eventStrings);
	}
	return 1;
}



int StringParser(CVectorString* vec , char * str)
{
	VectorClear( (*vec) ) ;

	char * it = strtok(str ,  "/ ,\n");
	if(it)
	{
		VectorAppend((*vec) , it);
		while(it = strtok(NULL , " ,\n"))
		{
			VectorAppend((*vec) , it);
		}
		return 1;
	}
	else
	{	if(*str != 0)
		{
			VectorAppend((*vec) , str);
			return 1;
		}
		return 0;
	}
}



int RunConsoleQuery()
{
	int run = 1;
	char buffer[1024];
	CVectorString vecStr;
	VectorInit(vecStr);
	printf("Welcome the html-c Binary Tree visualizer\n");
	printf("felbsn 2018\n");
	printf("Some available functions below\n");
	printf("%s\n", "base list (sorted)");
    int  i;
	for ( i = 0; i < commands.size; ++i)
	{
		printf("<> %s\n", commands.data[i].command);
	}


	while(run)
	{

		printf(">");
		fgets(buffer , 1024 , stdin);
		StringParser(&vecStr , buffer);

		int fncIndex;
		VectorBinarySearch(commands, vecStr.data[0], CommandComparator, fncIndex);

		if(fncIndex >= 0)
		{
			int result = 0;
		    result = commands.data[fncIndex].func(vecStr);

		    if(result)
			RunLoopCmds();

		}else
		{
			printf("invalid command\n");
		}

	}

	return 0;
}

