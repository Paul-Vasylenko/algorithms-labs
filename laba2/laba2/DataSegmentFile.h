#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct DataRecord {
	int keyValue;
	string dataValue;
	bool isDeleted;

	void parseLine(string);
	DataRecord(){
		this->keyValue = 0;
		this->dataValue = "";
		this->isDeleted = false;
	}
	DataRecord(int key, string data) {
		this->dataValue = data;
		this->keyValue = key;
		this->isDeleted = false;
	}
};


class DataSegmentFile
{
public:
	vector<DataRecord*> records;
	DataSegmentFile();

	void readFile();
	int insert(int, string);
	string getByRowNumber(int);
	void deleteByKey(int);
	void writeFile();
	string updateByRowNumber(int, string);
};

