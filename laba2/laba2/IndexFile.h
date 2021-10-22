#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct IndexRecord {
	int keyValue;
	int dataPointer;

	void parseLine(string line);
	IndexRecord() {
		keyValue = 0;
		dataPointer = 0;
	}
	IndexRecord(int key, int data) {
		keyValue = key;
		dataPointer = data;
	}
};

class IndexBlock {
public:
	int MAX_KEY_VALUE, MIN_KEY_VALUE;
	vector<IndexRecord*> records;
	
	IndexBlock(int,int);
	void pushNewRecord(IndexRecord*);

	IndexRecord* get(int);
	IndexRecord* binarySearch(int,int,int);
	bool add(int, int);
	void deleteByKey(int);

};

class IndexFile
{
	static const unsigned int MAX_KEY_VALUE = INT_MAX;
	static const unsigned int NUMBER_OF_BLOCKS = 4;//index file contains 4 blocks
	static const unsigned int MAX_BLOCK_SIZE = 1500;
public:
	vector<IndexBlock*> blocks;
	IndexBlock* overflowArea;

	IndexFile() {
		overflowArea = new IndexBlock(0, MAX_KEY_VALUE);

		int BLOCK_STEP = MAX_KEY_VALUE / NUMBER_OF_BLOCKS;
		int prevMax = 0;
		for (int i = 0; i < NUMBER_OF_BLOCKS; i++)
		{
			auto block = new IndexBlock(prevMax, prevMax + BLOCK_STEP);
			this->blocks.push_back(block);
			prevMax += BLOCK_STEP + 1;
		}

		this->readFile();
	}
	void readFile();

	IndexRecord* search(int);
	void insert(int, int);
	void writeFile();
	void deleteByKey(int);
};

