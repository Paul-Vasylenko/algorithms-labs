#include "DataSegmentFile.h"

DataSegmentFile::DataSegmentFile()
{
	this->readFile();
}

void DataSegmentFile::readFile()
{
	ifstream file("data_seg.csv");
	if (!file.is_open()) {
		cout << "No data segment file found;" << endl;
	}
	string line;
	getline(file, line);
	while (!file.eof()) {
		auto dataRecord = new DataRecord();
		if (line.empty()) {
			continue;
		}
		dataRecord->parseLine(line);
		this->records.push_back(dataRecord);
		getline(file, line);
	}
	if (!line.empty()) {
		auto dataRecord = new DataRecord();
		dataRecord->parseLine(line);
		this->records.push_back(dataRecord);
	}
}

int DataSegmentFile::insert(int key, string data)
{
	auto newRecord = new DataRecord(key,data);
	records.push_back(newRecord);
	ofstream file("data_seg.csv", ios::app);
	file << key << ',' << data << endl;
	return records.size();
}

string DataSegmentFile::getByRowNumber(int number)
{
	if(records.size() >= number)
	return this->records[number-1]->dataValue;
	return "Not found--system-reserved";
}

void DataSegmentFile::deleteByKey(int key)
{
	for (auto record : records) {
		if (record->keyValue == key) {
			record->isDeleted = true;
		}
	}
	this->writeFile();
}

void DataSegmentFile::writeFile()
{
	ofstream file("data_seg.csv");
	for (auto record : records) {
		if (record->isDeleted) {
			file << record->keyValue<< ',' << record->dataValue<<"[DELETED]" << endl;
		}
		else {
			file << record->keyValue << ',' << record->dataValue<< endl;
		}
	}
}

string DataSegmentFile::updateByRowNumber(int rowNumber, string newData)
{
	if (records.size() < rowNumber - 1) return "Not found";
	if (records[rowNumber - 1]->isDeleted) return "Not found(was deleted)";
	records[rowNumber - 1]->dataValue = newData;
	this->writeFile();
	return "Updated";
}

void DataRecord::parseLine(string line)
{
	//166468198,sdfsmdlfksdfl;kmsdfk
	if (line.find("[DELETED]") != string::npos) {
		this->keyValue = stoi(line.substr(0, line.find(',')));
		this->dataValue = line.substr(line.find(',') + 1, line.find("[DELETED]") - line.find(',') -1);
		this->isDeleted = true;
	}
	else {
		this->keyValue = stoi(line.substr(0, line.find(',')));
		this->dataValue = line.substr(line.find(',') + 1);
	}
}
