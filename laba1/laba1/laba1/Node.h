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
public:
	int** state;
	Node* parent;
	vector<Node*> children;

	Node(Node*);
	Node(Node* ,int**);

	bool checkStateForWin();


	Node* createNewState(int, int);
	vector<Node*> generateChildrenNodes(int);
};

