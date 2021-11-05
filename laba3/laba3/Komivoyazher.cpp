#include "Komivoyazher.h"

Komivoyazher::Komivoyazher(int numOfCities)
{
	this->numberOfCities = numOfCities;
	this->distanceMatrix = new float* [numOfCities];
	for (int i = 0; i < numOfCities; i++)
	{
		this->distanceMatrix[i] = new float[numOfCities];
	}

	for (int i = 0; i < numOfCities; i++)
	{
		for (int j = 0; j < numOfCities; j++)
		{
			distanceMatrix[i][j] = 0;
		}
	}

	for (int i = 0; i < numOfCities; i++)
	{
		for (int j = 0; j < numOfCities; j++)
		{
			if (i == j) distanceMatrix[i][j] = 0;
			else if (distanceMatrix[i][j] != 0) continue;
			else {
				int num = rand()%46 + 5;
				distanceMatrix[i][j] = distanceMatrix[j][i] = num;
			}
		}
	}
	//READ FROM FILE
	/*ifstream file;
	file.open("data.txt");

	for (int i = 0; i < numOfCities; i++)
	{
		string curDataLine;
		getline(file, curDataLine);
		for (int j = 0; j < numOfCities; j++)
		{
			int value = stoi(curDataLine.substr(0, curDataLine.find(' ')));
			curDataLine.erase(0, curDataLine.find(' ') + 1);
			distanceMatrix[i][j] = value;
		}
	}
	file.close();*/
}

void Komivoyazher::displayDistanceMatrix()
{
	for (int i = 0; i < this->numberOfCities; i++)
	{
		for (int j = 0; j < numberOfCities; j++)
		{
			cout << distanceMatrix[i][j] << '\t';
		}
		cout << endl;
	}
}
