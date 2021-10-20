#include "FileWorker.h"

void FileWorker::addToFile(int data)
{
	ofstream f("data.csv", ios_base::app);
	Data temp(this->keyCounter, data);
	if (!f.is_open()) {
		cout << "Error, no such file";
	}
	f << temp.key << ';' << temp.data << ';' << '\n';
}
