#include "Filehelper.h"

vector<Item> Filehelper::readItemsFromFile(string fname)
{
	ifstream f(fname);
	vector<Item> result;

	if (!f.is_open()) {
		cout << "No such file";
		return result;
	}
	
	string str;
	while (getline(f, str))
	{
		if (str[0] == '#') continue;
		string name = str.substr(0, str.find(';'));
		str.erase(0, str.find(';') + 1);
		int weight = stoi(str.substr(0, str.find(';')));
		str.erase(0, str.find(';') + 1);
		int price = stoi(str.substr(0, str.size()));
		Item temp(name,weight,price);

		result.push_back(temp);
	}
	return result;
}
