#pragma once
#include <cstddef>
#include <iostream>
#include <vector>
using namespace std;

class Node
{
	bool checkRow(int);
	bool checkCol(int);
	bool checkDiagonals(int, int);

	int countConflictsInColumnAfterRow(int, int);
	int countConflictsInDiagonals(int, int);

public:
	int** state;
	Node* parent;
	vector<Node*> children;
	int depth = 0;

	Node(Node*);
	Node(Node* ,int**);

	bool checkStateForWin();
	int countPairsOfBittenQueens();

	Node* createNewState(int, int);
	vector<Node*> generateChildrenNodes(int);
};

