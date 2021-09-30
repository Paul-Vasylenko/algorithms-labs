#include "Node.h"

Node::Node(Node* parentNode)
{
	parent = parentNode;
	son = NULL;
	brother = NULL;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			state[i][j] = 0;
		}
	}
}

Node::Node(Node* parentNode, int newState[8][8])
{
	parent = parentNode;
	son = NULL;
	brother = NULL;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++)
		{
			state[i][j] = newState[i][j];
		}
	}
}

