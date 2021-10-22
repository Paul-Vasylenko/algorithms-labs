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
		if(line.empty()){
			continue;
		}
		currentIndexRecord->parseLine(line);
		
		while (!(currentIndexRecord->keyValue >= this->blocks[currentBlock]->MIN_KEY_VALUE
			&& currentIndexRecord->keyValue <= this->blocks[currentBlock]->MAX_KEY_VALUE)) {
			currentBlock++;
		}
		blocks[currentBlock]->pushNewRecord(currentIndexRecord);
		getline(file, line);
	}
	getline(file, line);
	while (!file.eof()) {
		int currentBlock = 0;
		auto currentIndexRecord = new IndexRecord();
		if (line.empty()) {
			continue;
		}
		currentIndexRecord->parseLine(line);
		overflowArea->pushNewRecord(currentIndexRecord);
		getline(file, line);
	}
}

IndexRecord* IndexFile::search(int keyValue)
{
	for (auto block:blocks)
	{
		if (block->MAX_KEY_VALUE >= keyValue && block->MIN_KEY_VALUE <= keyValue) {
			auto result = block->get(keyValue);
			if (result == nullptr) {
				result = overflowArea->get(keyValue);
			}
			return result;
		}
	}
}

void IndexFile::insert(int key, int dataPointer)
{
	for (auto block : blocks) {
		if (key <= block->MAX_KEY_VALUE && key >= block->MIN_KEY_VALUE) {
			//auto record = new IndexRecord(key,dataPointer);
			if (block->records.size() < this->MAX_BLOCK_SIZE) {
				auto result = block->add(key, dataPointer);
				if (result) {
					this->writeFile();
				}
					return;
			}
			else {
				auto result = overflowArea->add(key, dataPointer);
				if (result) {
					this->writeFile();
				}
					return;
			}
		}

	}
}

void IndexFile::writeFile()
{
	ofstream file("index_seg.csv");
	for (auto block : blocks) {
		for (int i = 0; i < block->records.size(); i++)
		{
			file << block->records[i]->keyValue << ',' << block->records[i]->dataPointer << endl;
		}
	}
	file << "Overflow area" << endl;
	for (int i = 0; i < overflowArea->records.size(); i++)
	{
		file << overflowArea->records[i]->keyValue << ',' << overflowArea->records[i]->dataPointer << endl;
	}
	file.close();
}

void IndexFile::deleteByKey(int key)
{
	for (auto block : blocks) {
		if (key >= block->MIN_KEY_VALUE && key <= block->MAX_KEY_VALUE) {
			block->deleteByKey(key);
			this->writeFile();
		}
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

IndexRecord* IndexBlock::get(int key)
{
	if (records.size() == 0) return nullptr;
	if (records.size() == 1) return records[0]->keyValue == key ? records[0] : nullptr;
	auto result = binarySearch(key,0,records.size()-1);
	return result;
}

IndexRecord* IndexBlock::binarySearch(int key, int left, int right)
{
int iterationCounter = 0;
	while (left <= right) {
		iterationCounter++;
		int m = left + (right - left) / 2;
		if (records[m]->keyValue == key) {
			cout << "Iterations: " << iterationCounter << endl;
			return records[m];
		}
		if (records[m]->keyValue < key)
			left = m + 1;
		else
			right = m - 1;
	}
	cout << "Iterations: " << iterationCounter << endl;

	return nullptr;
}

bool IndexBlock::add(int key, int dataPointer)
{
	auto result = binarySearch(key, 0, records.size()-1);
	if (result == nullptr) {
		if (!records.empty()) {
			vector<IndexRecord*>::iterator iterator = records.begin();
			for (iterator; iterator < records.end(); iterator++) {
				if ((*iterator)->keyValue >= key) break;
			}
			auto newRecord = new IndexRecord(key, dataPointer);
			records.insert(iterator, newRecord);
		}
		else {
			auto newRecord = new IndexRecord(key, dataPointer);
			records.push_back(newRecord);
		}
		return true;
	}
	return false;
}

void IndexBlock::deleteByKey(int key)
{
	for (auto iterator = records.begin(); iterator < records.end(); ++iterator) {
		if ((*iterator)->keyValue == key) {
			records.erase(iterator);
			return;
		}
	}
}



void IndexRecord::parseLine(string line)
{
	//121655,17
	this->keyValue = stoi(line.substr(0, line.find(',')));
	this->dataPointer = stoi(line.substr(line.find(',') + 1));
}
