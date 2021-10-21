#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct DataRecord {
	int keyValue;
	string dataValue;

	void parseLine(string);
};


class DataSegmentFile
{
public:
	vector<DataRecord*> records;
	DataSegmentFile();

	void readFile();
};

