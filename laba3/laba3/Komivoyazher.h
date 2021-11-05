#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Komivoyazher
{
public:
	float** distanceMatrix;
	int numberOfCities;
	Komivoyazher(int numOfCities);
	void displayDistanceMatrix();
};

