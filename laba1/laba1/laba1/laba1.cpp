#include <iostream>
#include <string>
#include "Node.h"	
using namespace std;

int main()
{
	string method;
	cout << "What do you want to use? LDFS/A* : ";
	getline(cin,method);
	if (method == "LDFS" || method == "ldfs") {
		const int depthLimit = 20;

	}
	else if (method == "A*" || method == "a*") {
	}
	else {
		cout << "ERROR" << endl;
	}
	return 0;
}

