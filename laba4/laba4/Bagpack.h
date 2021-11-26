#pragma once
#include "Item.h"
#include <vector>
#include "Filehelper.h"
#include <algorithm>
using namespace std;
class Bagpack
{
	vector<Item> itemList;
	vector<Item> allItems;
	int P;
public:
	Bagpack() { P = 0; };
	Bagpack(int);
	void createItems();
	vector<vector<bool>> generatePlots(int);
	int totalWeight(vector<bool>, int);
	int totalPrice(vector<bool>);
	vector<bool> sendForagers(vector<bool>, int);
	vector<int> getSortedByPricePerWeight();
	void displayItem(int);
};

