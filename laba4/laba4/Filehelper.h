#pragma once
#include <vector>
#include "Item.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

struct Filehelper
{
	static vector<Item> readItemsFromFile(string);
};

