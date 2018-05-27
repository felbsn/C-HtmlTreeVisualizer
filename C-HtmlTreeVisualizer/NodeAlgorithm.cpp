#pragma warning(disable:4996)
#include "NodeAlgorithm.h"



 /* basic function declerations*/
 bNode * newNode()
{
	bNode* node =(bNode*) malloc(sizeof(bNode));
	node->value = 0;
	node->data = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

bTree newTree()
{
	bTree tree;
	tree.root = NULL;
	tree.size = 0;
	return tree;
}



void _freeChain(bNode* node)
{
	if(node != NULL)
	{

		_freeChain(node->left);
		_freeChain(node->right);
		free(node);
	}
}

void freeNodeChain(bNode** root)
{
		if(*root)
		{
			_freeChain(*root);
			*root = NULL;
		}

}

 bNode * newNodeValue(int value)
{
	bNode* node = (bNode*)malloc(sizeof(bNode));
	node->value = value;
	node->data = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}


 void NodeAssignData(bNode* node ,void* data)
{
	if(node->data)
		free(node->data);

	node->data = data;
}


void ArrayToNodePtr(bNode** node  ,bNode** arr ,int left , int right)
{
	if(right >= left)
	{
		int curIndex = left + (right-left)/2;

		*node = arr[curIndex];

		ArrayToNodePtr(&(*node)->left,arr  ,  left , curIndex-1 );
		ArrayToNodePtr(&(*node)->right ,arr  ,  curIndex+1 , right );
	}
}

int ReadTreeArrayFrom(const char* filePath ,bNode** root, void* (*functor)())
{
	FILE * fo = fopen(filePath , "r");
	if(fo)
	{

		CVectorNodePTR vec;  
		VectorInit(vec);
		char buffer[1024];

		while(!feof(fo))
		{
			fgets(buffer , 1024 , fo);

			char* delim =strtok(buffer , ", -");
			while(delim)
			{
				bNode* tmp = newNodeValue(atoi(delim));
				if(functor)tmp->data = functor();
				VectorAppend(vec , tmp);
				delim  = strtok(NULL , ", -");
			}
		}

		VectorSort(vec , NodeGreater);

		freeNodeChain(root);
		ArrayToNodePtr(root ,vec.data , 0,vec.size );
		VectorFree(vec);
		fclose(fo);
		return 1;
	}
	return 0;
}


bNode* FindNode(bNode* root , int value)
{

	while(root != NULL && root->value != value)
	{
		if(root-> value > value)
		{
			root = root->left;
		}else
		{
			root = root->right;
		}
	}
	return root;

}

void NodePtrToArray(bNode* node , CVectorNodePTR* vec)
{
	if(node == NULL )
		return;
	else
	{
	NodePtrToArray(node->left , vec);
	VectorAppend( (*vec) , node );
	NodePtrToArray(node->right , vec);
	}

}


void ReBuildTree(bNode** node ,bNode** nodeArray ,int left ,int  right )
{
	if(right >= left)
	{
		int curIndex = left + (right-left)/2;

		*node = nodeArray[curIndex];


		(*node)->left = (*node)->right = NULL;

		ReBuildTree(&(*node)->left,nodeArray  ,  left , curIndex-1 );

		ReBuildTree(&(*node)->right ,nodeArray  ,  curIndex+1 , right );
	}
}

void NodeUnion(bNode* leftNode , bNode* rightNode , bNode** root)
{
	CVectorNodePTR vec; 
	VectorInit(vec)
	NodePtrToArray(leftNode , &vec);
	NodePtrToArray(rightNode , &vec);



	if(vec.size > 0)
	ReBuildTree(root , vec.data ,0 , vec.size-1);


	VectorFree(vec);


}

void BalanceNodes(bNode** root)
{
	CVectorNodePTR vec; 
	VectorInit(vec);
	NodePtrToArray(*root , &vec);
	if(vec.size > 0)
	ReBuildTree(root , vec.data ,0 , vec.size-1);
	VectorFree(vec);

}

int DeleteNode(bNode** root , int value)
{
	bNode** nodeAddr  = root;
	bNode* node = *root;

	while(node != NULL && node->value != value)
	{
		//reach value by iterate while
		if(node-> value > value)
		{
			nodeAddr = &node->left;
			node = node->left;
		}else
		{
			nodeAddr =  &node->right;
			node = node->right;
		}
	}
	if(node != NULL)
	{
		printf("node found and try to delete [%d]\n",node->value );

		*nodeAddr = NULL;
		NodeUnion(node->left , node->right,nodeAddr);

		// free  , deleted node
		free(node);
		return 1;
	}
	else
		return 0;
}


int TreeElementCount(bNode* root )
{
	if(root == NULL)
		return 0;
	else
	{
		int baseCount;
		baseCount = TreeElementCount(root->left);
		baseCount +=TreeElementCount(root->right);
		baseCount++;
		return baseCount;
	}
}


void TreeBalance(bNode** root)
{
	if(*root != NULL)
	{
		int difference = TreeDepth((*root)->left) - TreeDepth((*root)->right);
		#ifdef DEBUG
		printf("base differences:%d  at root value:%d ",difference , (*root)->value);
		#endif

		difference = difference < 0  ? -difference : difference;
		if( difference >= TREE_BALANCE_TOLERANCE )
		{
			#ifdef DEBUG
			printf("balance occurs   . .  .\n" );
			#endif

			BalanceNodes(root);
		}
		else
		{
			#ifdef DEBUG
			printf("Search upper case . .  .\n" );
			#endif

			TreeBalance(&(*root)->left);
			TreeBalance(&(*root)->right);
		}
	}
}


int TreeDepth(bNode* root )
{
	if(root == NULL)
	return 0;
	else
	{
		int leftSideDepth ,rightSideDepth ;
		leftSideDepth = TreeDepth(root->left);
		rightSideDepth  =TreeDepth(root->right);

		if(rightSideDepth >= leftSideDepth)
		{
			rightSideDepth++;
			return  rightSideDepth;
		}else
		{
			leftSideDepth++;
			return  leftSideDepth;
		}
	}

}


void _Inserter(bNode** parent  ,bNode* node)
{
	if(node->value >= (*parent)->value)
	{
		if((*parent)->right == NULL)
		{
			(*parent)->right = node;

			return;
		}else
		{
			_Inserter(&(*parent)->right , node);
			TreeBalance(parent);

		}
	}
	else
	{
		if((*parent)->left == NULL)
		{
			(*parent)->left = node;
			return;
		}else
		{
			_Inserter(&(*parent)->left , node);
			TreeBalance(parent);
		}


	}

}
void InsertNode(bNode** root , bNode* node)
{
	if(*root == NULL)
	{
		*root = node;
	}else
	{
	_Inserter(root , node);
	}


}

void InsertRawLeft(bNode* parent , bNode* node)
{

	if(parent->left == NULL)
	{
		parent->left = node;
	}else
	{
		bNode* temp;
		temp = parent->left;
		parent->left = node;
		node->left = temp;
	}
}

void InsertRawRight(bNode* parent , bNode* node)
{

	if(parent->right == NULL)
	{
		parent->right = node;
	}else
	{
		bNode* temp;
		temp = parent->right;
		parent->right = node;
		node->right = temp;
	}
}

/* node functor */
int NodeGreater(bNode* lhs , bNode* rhs)
{
	if(lhs->value >= rhs->value )
		return 1;
	else
		return 0;
}

int NodeLower(bNode* lhs , bNode* rhs)
{
	if(lhs->value < rhs->value )
		return 1;
	else
		return 0;
}






