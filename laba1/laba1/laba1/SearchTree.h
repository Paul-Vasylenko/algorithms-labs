#pragma once
#include "Node.h"
class SearchTree
{
public:
	Node* root;
	
	SearchTree(Node*);

	void Insert(Node* insertIntoNode, int data[8][8]);
};

