#include <iostream>
#include "DenseIndexFile.h"
#include <ctime>
#include <random>

using namespace std;

int main() {
	srand(time(NULL));
	auto denseIndexFile = new DenseIndexFile();
	cout << "COMMANDS: \nSELECT data_key \nINSERT data_value \nDELETE data_key \nUPDATE data_key data_value \nQUIT - for end of the program\nTRUNC DATABASE\n\n";
	string command = "";
	try {
		while (command != "QUIT") {
			cout << "Enter command: ";
			getline(cin, command);
			if (command == "TRUNC DATABASE") {
				denseIndexFile->dataSegment->records.clear();
				for (auto block : denseIndexFile->indexSegment->blocks) {
					block->records.clear();
				}
				ofstream data("data_seg.csv");
				data.close();
				ofstream index("index_seg.csv");
				index << "Overflow area";
			}
			else if (command == "FILL") {
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> distribution(0, INT_MAX);
				for (int i = 0; i < 10000; i++)
				{
					string data = to_string(i);
					int key;
					string found = "";
					while (found != "Not found--system-reserved") {
						key = distribution(gen);
						found = denseIndexFile->getData(key);
					}
					denseIndexFile->insert(key, data);
				}
			}
			else {
				ifstream dataseg("data_seg.csv");
				if (!dataseg.is_open()) {
					cout << "CREATE DATABASE FIRST" << endl;
					return -1;
				}
				dataseg.close();
				ifstream indexseg("index_seg.csv");
				if (!indexseg.is_open()) {
					cout << "CREATE DATABASE FIRST" << endl;
					return 1;
				}
				indexseg.close();
				if (command.find("INSERT") == 0) {
					random_device rd;
					mt19937 gen(rd());
					uniform_int_distribution<> distribution(0, INT_MAX);
					string data = command.substr(command.find("INSERT") + 7);
					int key;
					string found = "";
					while (found != "Not found--system-reserved") {
						key = distribution(gen);
						found = denseIndexFile->getData(key);
					}
					denseIndexFile->insert(key, data);
					cout << "Added" << endl;
				}
				else if (command.find("SELECT") == 0) {
					int key = stoi(command.substr(command.find("INSERT") + 7));
					string result = denseIndexFile->getData(key);
					cout << "Found: " << result << endl;
				}
				else if (command.find("DELETE") == 0) {
					int key = stoi(command.substr(command.find("DELETE") + 7));
					denseIndexFile->deleteByKey(key);
					cout << "Deleted" << endl;
				}
				else if (command.find("UPDATE") == 0) {
					//update 124658 78
					string all = command.substr(command.find(' ') + 1);
					int key = stoi(command.substr(7, command.find_last_of(' ') - 7));
					string newData = all.substr(all.find(' ') + 1);
					string res = denseIndexFile->updateByKey(key, newData);
					cout << res << endl;
				}
				else {
					if(command!="QUIT")
					cout << "Unknown command" << endl;
				}
			}
		}
	}
	catch (exception e) {
		cout << e.what();
	}
	return 0;
}