#pragma once
#include <string>
using namespace std;
class Item
{
	string name;
	int weight;
	int price;
public:
	Item(string, int, int);
	Item() { name = ""; weight = 0; price = 0; };
	string getName();
	int getWeight();
	int getPrice();
};

