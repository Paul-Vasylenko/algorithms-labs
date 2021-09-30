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

void SearchTree::displayBoard(int** board)
{
	const int size = 8;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
}


