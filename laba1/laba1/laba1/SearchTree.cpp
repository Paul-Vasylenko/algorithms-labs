#include "SearchTree.h"

SearchTree::SearchTree(Node* node, int newDepth)
{
	root = node;
	depth = newDepth;
}

void SearchTree::Insert(Node* nodeToInsert)
{
	root->children.push_back(nodeToInsert);
}

int deadblockCounter = 0;
int iterationCounter = 0;
int** SearchTree::LDFS(SearchTree tree, int depthLimit, int* ldfsStateConuter)
{
	int statesInMemory = 8 * depthLimit + 1;
	bool isWin = tree.root->checkStateForWin();
	iterationCounter++;
	if (isWin) {
		cout <<endl<< "Dead block counter: " << deadblockCounter<<endl;
		cout << endl << "Iteration counter: " << iterationCounter << endl;
		cout << endl << "States in memory: " << statesInMemory << endl;
		return tree.root->state;
	}
	else{
		if (tree.depth > depthLimit) {
			deadblockCounter++;
			return nullptr;
		}
		vector<Node*> childrens = tree.root->generateChildrenNodes(tree.depth);
		for (int j = 0; j < childrens.size(); j++)
		{
			tree.Insert(childrens[j]);
		}
		for (int j = 0; j < childrens.size(); j++)
		{
			int** result = new int* [8];
			//copy state
			for (int i = 0; i < 8; i++)
			{
				result[i] = new int[8];
			}
			(*ldfsStateConuter)++;
			result = SearchTree::LDFS(SearchTree(childrens[j], tree.depth+1), depthLimit, ldfsStateConuter);
			if (result != nullptr) {
				return result;
			}
		}
		if (tree.depth == 0) {
			cout << endl << "Dead block counter: " << deadblockCounter << endl;
			cout << endl << "Iteration counter: " << iterationCounter << endl;
			statesInMemory = 0;
			cout << endl << "States in memory: " << statesInMemory << endl;
		}

		return nullptr;
	}
}


class Compare
{
public:
	bool operator() (Node* a, Node* b)
	{
		return a->countPairsOfBittenQueens()+a->depth*3 > b->countPairsOfBittenQueens()+b->depth*3;
	}
};

void printQueue(priority_queue<Node*, vector<Node*>, Compare> q) {
	while (!q.empty()) {
		cout << '\n';
		SearchTree::displayBoard(q.top()->state);
		q.pop();
	}
}

int** SearchTree::ASTAR(SearchTree tree)
{
	int iterationCounter=0;
	int deadBlockCounter = 0;
	priority_queue<Node*, vector<Node*>, Compare> open;
	vector<Node*> closed;
	open.push(tree.root);
	while (!open.empty()) {
		iterationCounter++;
		Node* current = open.top();
		open.pop();
		if (closed.size() > 0) {
			if (current->depth < closed[closed.size() - 1]->depth) {
				deadBlockCounter++;
			};
		}
		if (current->checkStateForWin()) {
			cout << endl << "Iterations: " << iterationCounter;
			cout << endl << "deadBlockCounter: " << deadBlockCounter;
			cout << endl << "Total visited: " << closed.size()+1;
			cout << endl << "In the queue at the end: " << open.size();

			return current->state;
		}
		vector<Node*> childrens = current->generateChildrenNodes(current->depth+1);
		current->children = childrens;
		for (int i = 0; i < childrens.size(); i++)
		{
			childrens[i]->depth = current->depth+1;
			open.push(childrens[i]);
		}
		closed.push_back(current);
	}
	cout << endl << "Iterations: " << iterationCounter;
	cout << endl << "deadBlockCounter: " << deadBlockCounter;
	cout << endl << "Total visited: " << closed.size()+1;
	cout << endl << "In the queue at the end: " << open.size();

	return nullptr;
}

void SearchTree::displayBoard(int** board)
{
	const int size = 8;
	if (board == nullptr) {
		cout << "not found";
		return;
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
}


