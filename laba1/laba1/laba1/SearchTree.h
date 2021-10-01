#pragma once
#include "Node.h"
#include <queue>
class SearchTree
{
public:
	Node* root;
	int depth;
	SearchTree(Node*, int);

	void Insert(Node* insertIntoNode);

	static int** LDFS(SearchTree tree, int depthLimit);
	static int** ASTAR(SearchTree tree);

	static void displayBoard(int** board);

};

