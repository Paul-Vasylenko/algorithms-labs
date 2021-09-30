#include <iostream>
#include <string>
#include <ctime>
#include "SearchTree.h"
using namespace std;

int** generateState(int**);
void displayBoard(int**);

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
	displayBoard(root->state);
	cout << endl<<"CHECK FOR EVERY ROW!"<<root->checkStateForWin();
	SearchTree tree(root);
	if (method == "1") {
		const int depthLimit = 20;

	}
	else if (method == "2") {
	}
	else {
		cout << "ERROR" << endl;
	}
	return 0;
}

int** generateState(int** result) {
	const int size = 8;

	bool rowhasQueen = false;
	for (int i = 0; i < size; i++)
	{
		rowhasQueen = false;
		for (int j = 0; j < size; j++) {
			int queen = rand() % 2;
			if (rowhasQueen) {
				result[i][j] = 0;
			}
			else {
			result[i][j] = queen;
			}
			if (queen == 1) {
				rowhasQueen = true;
			}
		}
	}

	return result;
}

void displayBoard(int** board) {
	const int size = 8;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j] << '\t';
		}
		cout << endl;
	}
}