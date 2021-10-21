#include "IndexFile.h"

void IndexFile::readFile()
{
	ifstream file("index_seg.csv");
	if (!file.is_open()) {
		cout << "No index file found";
		return;
	}
	string line;
	getline(file, line);
	while (line!="Overflow area") {
		int currentBlock = 0;
		auto currentIndexRecord = new IndexRecord();
		currentIndexRecord->parseLine(line);
		
		while (!(currentIndexRecord->keyValue >= this->blocks[currentBlock]->MIN_KEY_VALUE
			&& currentIndexRecord->keyValue <= this->blocks[currentBlock]->MAX_KEY_VALUE)) {
			currentBlock++;
		}
		blocks[currentBlock]->pushNewRecord(currentIndexRecord);
		getline(file, line);
	}
}

IndexBlock::IndexBlock(int min=0, int max= INT_MAX)
{
	this->MAX_KEY_VALUE = max;
	this->MIN_KEY_VALUE = min;
}

void IndexBlock::pushNewRecord(IndexRecord* rec)
{
	this->records.push_back(rec);
}



void IndexRecord::parseLine(string line)
{
	//121655,17
	this->keyValue = stoi(line.substr(0, line.find(',')));
	this->dataPointer = stoi(line.substr(line.find(',') + 1));
}
