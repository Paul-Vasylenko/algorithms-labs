#pragma once
#include <cstddef>
using namespace std;

class Node
{
public:
	int state[8][8];
	Node* parent;
	Node* son;
	Node* brother;

	Node(Node*);
	Node(Node* ,int[8][8]);
};

