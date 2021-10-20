#include <iostream>
#include "FileWorker.h"
#include "Data.h"
using namespace std;

int main()
{
	FileWorker fileworker;
	ofstream f("data.csv", ios_base::trunc);
	f.close();
	for (int i = 0; i < 10; i++) {
		fileworker.addToFile(i);
	}
}

