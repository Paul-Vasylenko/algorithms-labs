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

int** SearchTree::LDFS(SearchTree tree, int depthLimit)
{
	bool isWin = tree.root->checkStateForWin();
	if (isWin) {
		return tree.root->state;
	}
	else{
		if (tree.depth > depthLimit) {
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
			result = SearchTree::LDFS(SearchTree(childrens[j], tree.depth+1), depthLimit);
			if (result != nullptr) {
				return result;
			}
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
	priority_queue<Node*, vector<Node*>, Compare> open;
	open.push(tree.root);
	while (!open.empty()) {
		Node* current = open.top();
		open.pop();
		if (current->checkStateForWin()) {
			return current->state;
		}
		vector<Node*> childrens = current->generateChildrenNodes(current->depth+1);
		current->children = childrens;
		for (int i = 0; i < childrens.size(); i++)
		{
			childrens[i]->depth = current->depth+1;
			open.push(childrens[i]);
		}
	}
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


