#pragma once
#include <vector>
#include <cmath>
#include "Ant.h"
#include <iostream>
using namespace std;
class AntColony
{
	int alpha = 2;
	int beta = 4;
	float evaporation = 0.4;
	int numberOfAnts = 30;
	float randomFactor = 0.01;

	int maxIterations = 1000;

	int numberOfCities;
	double Lmin=170; //calc
	float** graph;
	float** sightMatrix;
	float** trails;
	vector<Ant> ants;
	double* probabilities;

	int currentIndex;

	int* bestTourOrder;
	float bestTourLength;

	void putAntsOnPositions();
	void setStartTrails();
	void setSightMatrix();
	void moveAnts();
	void calculateProbabilities(Ant ant);
	int selectNextCity(Ant ant);
	void updateTrails();
	void updateBestSolution();
public:
	AntColony(float** generatedMatrix, int size);
	int* solve();
};

