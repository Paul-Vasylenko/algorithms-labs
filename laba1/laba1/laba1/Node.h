#pragma once
#include <cstddef>
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
};

