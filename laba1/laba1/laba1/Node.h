#pragma once
#include <cstddef>
#include <iostream>

using namespace std;

class Node
{
public:
	int** state;
	Node* parent;
	Node* son;
	Node* brother;

	Node(Node*);
	Node(Node* ,int**);

	bool checkStateForWin();
	bool checkRow(int);
	bool checkCol(int);
	bool checkDiagonals(int, int);
};

