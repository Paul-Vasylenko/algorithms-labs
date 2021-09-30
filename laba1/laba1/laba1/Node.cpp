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

Node::Node(Node* parentNode, int** newState)
{
	state = new int* [8];
	for (int i = 0; i < 8; i++)
	{
		state[i] = new int[8];
	}
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

bool Node::checkStateForWin()
{
	const int length = 8;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (state[i][j] == 1) {
				if (!this->checkRow(i)) return false;
				if (!this->checkCol(j)) return false;
			}
		}
	}
	return true;
}

bool Node::checkRow(int row)
{
	int counter = 0;
	for (int j = 0; j < 8; j++)
	{
		if (state[row][j] == 1) counter++;
	}
	return counter == 1;
}

bool Node::checkCol(int col)
{
	int counter = 0;
	for (int i = 0; i < 8; i++)
	{
		if (state[i][col] == 1) counter++;
	}
	return counter == 1;
}

