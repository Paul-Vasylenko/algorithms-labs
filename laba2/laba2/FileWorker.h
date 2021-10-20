#pragma once
#include <iostream>
#include <fstream>
#include "Data.h"
using namespace std;

class FileWorker
{
	int keyCounter = 0;
public:
	void addToFile(int data);
};

