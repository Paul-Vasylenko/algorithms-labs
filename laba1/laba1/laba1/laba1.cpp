#include <iostream>
#include <string>
#include <ctime>
#include "SearchTree.h"
using namespace std;

int** generateState(int**);

int main()
{
	srand(time(NULL));
	string method;
	cout << "What do you want to use? 1-LDFS/2-A* : ";
	getline(cin,method);
	int** initialState;
	int size = 8;
	initialState = new int* [size];
	for (int i = 0; i < size; i++)
	{
		initialState[i] = new int[size];
	}
	initialState = generateState(initialState);
	Node* root = new Node(nullptr, initialState);
	cout << endl << "===============" << endl << "INITIAL STATE"<<endl << "===============" << endl;
	SearchTree::displayBoard(root->state);
	SearchTree tree(root, 0);
	if (method == "1") {
		const int depthLimit = 7;
		int** result = new int* [8];
		for (int i = 0; i < 8; i++) {
			result[i] = new int[8];
		}
		result = SearchTree::LDFS(tree, depthLimit);
		cout << endl << "===============" << endl << "RESULT" << endl << "===============" << endl;
		SearchTree::displayBoard(result);

	}
	else if (method == "2") {
		int** result = new int* [8];
		for (int i = 0; i < 8; i++) {
			result[i] = new int[8];
		}
		result = SearchTree::ASTAR(tree);
		cout << endl << "===============" << endl << "RESULT" << endl << "===============" << endl;
		SearchTree::displayBoard(result);
	}
	else {
		cout << "ERROR" << endl;
	}
	return 0;
}

int** generateState(int** result) {
	const int size = 8;
	for (int i = 0; i < size; i++)
	{
		int queen = rand() % 8;

		for (int j = 0; j < size; j++) {
			if (j == queen) {
				result[i][j] = 1;
			}
			else {
				result[i][j] = 0;
			}
		}
	}
	return result;
}

