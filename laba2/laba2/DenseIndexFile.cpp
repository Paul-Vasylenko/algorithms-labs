#include "DenseIndexFile.h"

bool DenseIndexFile::insert(int key, string data)
{
	if (indexSegment->search(key) != nullptr) {
		return false;
	}
	auto dataPointer = dataSegment->insert(key, data);
	indexSegment->insert(key, dataPointer);
	return true;
}

string DenseIndexFile::getData(int key)
{
	for (auto block : this->indexSegment->blocks) {
		if (key >= block->MIN_KEY_VALUE && key <= block->MAX_KEY_VALUE) {
			IndexRecord* result = block->get(key);
			if (result == nullptr) {
				auto result1 = this->indexSegment->overflowArea->get(key);
				if (result1 == nullptr) return "Not found--system-reserved";
				string found1 = this->dataSegment->getByRowNumber(result1->dataPointer);
				return found1;
			}
			string found = this->dataSegment->getByRowNumber(result->dataPointer);
			return found;
		}
	}
	
}

void DenseIndexFile::deleteByKey(int key)
{
	this->dataSegment->deleteByKey(key);
	this->indexSegment->deleteByKey(key);
}

string DenseIndexFile::updateByKey(int key, string newData)
{
	for (auto block : this->indexSegment->blocks) {
		if (key >= block->MIN_KEY_VALUE && key <= block->MAX_KEY_VALUE) {
			IndexRecord* result = block->get(key);
			if (result == nullptr) {
				return "Not found";
			}
			string res = this->dataSegment->updateByRowNumber(result->dataPointer, newData);
			return res;
		}
	}
}
