#pragma once
#include "Node.h"
class SearchTree
{
public:
	Node* root;
	int depth;
	SearchTree(Node*, int);

	void Insert(Node* insertIntoNode);

	static int** LDFS(SearchTree tree, int depthLimit);
	static void displayBoard(int** board);

};

