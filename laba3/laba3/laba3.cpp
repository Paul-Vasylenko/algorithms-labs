#include <iostream>
#include <vector>
#include <string>
#include "Komivoyazher.h"
#include "AntColony.h"
#define SIZE 10
using namespace std;


int main()
{
	srand(time(0));
	Komivoyazher komivoyazher(100);
	AntColony antColony(komivoyazher.distanceMatrix, 100);

	antColony.solve();
}

