#include "Node.h"

Node::Node(Node* parentNode)
{
	parent = parentNode;
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
				if (!this->checkDiagonals(i, j)) return false;
			}
		}
	}
	return true;
}

int Node::countPairsOfBittenQueens()
{
	const int length = 8;
	int counter = 0;
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if (state[i][j] == 1) {
				counter += this->countConflictsInColumnAfterRow(i, j);
				counter += this->countConflictsInDiagonals(i, j);
			}
		}
	}
	return counter;
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

bool Node::checkDiagonals(int row, int col)
{
	int counter = 0;
	for (int i = row, j = col; i < 8 && j < 8; ++i, ++j)
	{
		if (state[i][j] == 1)counter++;
	}

	for (int i = row+1, j=col-1;j>=0 && i<8;i++, j--)
	{
		if (state[i][j] == 1)counter++;
	}

	return counter == 1;
}

int Node::countConflictsInDiagonals(int row, int col)
{
	int counter = 0;
	for (int i = row, j = col; i < 8 && j < 8; ++i, ++j)
	{
		if (state[i][j] == 1)counter++;
	}

	for (int i = row + 1, j = col - 1; j >= 0 && i < 8; i++, j--)
	{
		if (state[i][j] == 1)counter++;
	}

	return counter;
}

int Node::countConflictsInColumnAfterRow(int row, int col)
{
	int counter = 0;
	const int length = 8;
	row++;
	for (int i = row; i < length; i++)
	{
		if (state[i][col] == 1) {
			counter++;
		}
	}
	return counter;
}

Node* Node::createNewState(int row, int col)
{
	int** stateCopy = new int* [8];
	//copy state
	for (int i = 0; i < 8; i++)
	{
		stateCopy[i] = new int[8];
	}
	//copy values
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			stateCopy[i][j] = state[i][j];
		}
	}
	//move queen
	for (int j = 0; j < 8; j++)
	{
		if (stateCopy[row][j] == 1 && col != j) {
			stateCopy[row][j] = 0;
		}
		else if (j == col) {
			stateCopy[row][col] = 1;
		}
	}
	//new node
	Node* nodeNewState = new Node(nullptr, stateCopy);
	return nodeNewState;
}

vector<Node*> Node::generateChildrenNodes(int row)
{
	vector<Node*> childrenNodes;
	for (int j = 0; j < 8; j++)
	{
		Node* newNode = this->createNewState(row, j);
		if (newNode != NULL) {
			childrenNodes.push_back(newNode);
		}
	}
	return childrenNodes;
}

