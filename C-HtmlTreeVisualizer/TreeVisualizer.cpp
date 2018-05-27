#pragma warning(disable:4996)
#include "TreeVisualizer.h"



static int nodeID;
static void (*handlerFunc)( FILE* fo  ,void* data) = NULL;
static FILE* fo;







int _Packager(bNode* node ,int depth, int order )
{			
	 	    int c0 = -1;
	 	    int c1 = -1;


	 	   if(node->left != NULL)
			{
				
		       c0 = _Packager(node->left , depth+1 , order*2-1) ;
		       fprintf(fo, ",\n");
			}
	 	    if(node->right != NULL)
	 	    {
	 	    	
			   c1 = _Packager(node->right , depth+1 , order*2 );
			   fprintf(fo, ",\n");
	 	    }

	 	    int id = nodeID;
	 	    nodeID++;

	 	    if(handlerFunc)
	 	    {
	 	    	fprintf(fo, "[\"");
	 	    	if(node->data != NULL )
	 	    	handlerFunc(fo , node->data);
	 	    	fprintf(fo, "\" , %d , %d ,%d , %d ]", c0, c1 ,order , node->value);
	 	    }
	 	    else
	 	    {
	 	    	fprintf(fo, "[\"%s\" , %d , %d ,%d , %d ]","node" , c0, c1 ,order , node->value);
	 	    }

	 	// 	printf("NodeID: %d Val:%d   C( L:%d , R:%d ) _order:%d _depth:%d\n" , id , node->value , c0 , c1, order , depth);
	 	    return id;
}



int PackageTree(bNode* root, const char* outputFile, void(*func)(FILE*, void*))
{	

	// package def
	// [["data packet" ,(int left child) , (int right child ) ,(row order) ,(node value) ],

	if(root == NULL)
	{
		// reset existing data
		fo = fopen(outputFile , "w+");
		fclose(fo);
		return 0;
	}

	nodeID = 0;
	handlerFunc = func;
	fo = fopen(outputFile , "w+");
	fprintf(fo, "%s\n", "data = [");
 	int rootIndex = _Packager(root , 0, 1 );




 	fprintf(fo, "]; \n rootIndex = %d;", rootIndex);
	fclose(fo);
	return 1;
}



void _PrintTreeInOrder(bNode* root , void (*functor)(void*))
{
	if(root != NULL)
	{
	_PrintTreeInOrder(root->left , functor);
	
	printf(" (%d)" , root->value);
	if(functor){printf(": ");functor(root->data);}	

	_PrintTreeInOrder(root->right , functor);
 
	}
}


void PrintTreeInOrder(bNode* root , void (*functor)(void*))
{
	if(root != NULL)
	{
	_PrintTreeInOrder(root , functor);
	printf("\n");
	}
	else
	{
	printf("%s\n", "Tree is empty");
	}

}


void _PrintTreeGreater(bNode* root , int value)
{
	if(root != NULL)
	{

		if(root->value >= value)
		{

				if(root->value != value)
				{
					
					_PrintTreeGreater(root->left , value);
					printf("values %d \n", root->value);
				}	
				

				_PrintTreeGreater(root->right , value);

		}

		
	}

}

void PrintTreeGreater(bNode* root  ,int value , void (*functor)(void*))
{
	if(root != NULL)
	{
		_PrintTreeGreater(root , value);

	}else
	{
		printf("%s\n", "Tree is empty");
	}

}