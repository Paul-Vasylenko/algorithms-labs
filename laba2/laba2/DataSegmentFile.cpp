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
		dataRecord->parseLine(line);
		this->records.push_back(dataRecord);
		getline(file, line);
	}
	auto dataRecord = new DataRecord();
	dataRecord->parseLine(line);
	this->records.push_back(dataRecord);
}

void DataRecord::parseLine(string line)
{
	//166468198,sdfsmdlfksdfl;kmsdfk
	this->keyValue = stoi(line.substr(0, line.find(',')));
	this->dataValue = line.substr(line.find(',') + 1);
}
