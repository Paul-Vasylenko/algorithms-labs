#include "Item.h"

Item::Item(string name, int weight, int price)
{
	this->name = name;
	this->weight = weight;
	this->price = price;
}

string Item::getName()
{
	return this->name;
}

int Item::getWeight()
{
	return this->weight;
}

int Item::getPrice()
{
	return this->price;
}
