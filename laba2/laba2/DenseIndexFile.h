#pragma once
#include <iostream>
#include "IndexFile.h"
#include "DataSegmentFile.h"
using namespace std;
class DenseIndexFile
{

public:
	IndexFile* indexSegment;
	DataSegmentFile* dataSegment;
	DenseIndexFile() {
		indexSegment = new IndexFile();
		dataSegment = new DataSegmentFile();
	}

	bool insert(int, string);
	string getData(int);
	void deleteByKey(int);
	string updateByKey(int, string);
};

