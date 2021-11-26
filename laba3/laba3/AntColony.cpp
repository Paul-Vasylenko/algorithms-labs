#include "AntColony.h"

AntColony::AntColony(float** generatedMatrix, int size)
{
	graph = new float* [size];
	for (int i = 0; i < size; i++)
	{
		graph[i] = new float[size];
	}
	graph = generatedMatrix;

	trails = new float* [size];
	for (int i = 0; i < size; i++)
	{
		trails[i] = new float[size];
	}

	sightMatrix = new float* [size];
	for (int i = 0; i < size; i++)
	{
		sightMatrix[i] = new float[size];
	}

	probabilities = new double [size];
	numberOfCities = size;
	bestTourOrder = new int[size];
	for (int i = 0; i < size; i++)
	{
		bestTourOrder[i] = 0;
	}
	for (int i = 0; i < numberOfAnts; i++)
	{
		ants.push_back(Ant(numberOfCities));
	}
}

void AntColony::setAnts()
{
	for (int i = 0; i < numberOfAnts; i++)
	{
		ants[i].forget();
		int cityNum = rand() % numberOfCities;
		ants[i].visitCity(-1, cityNum);
	}
	currentIndex = 0;
}

int* AntColony::solve()
{
	getLMin();
	setStartTrails();
	setSightMatrix();
	for (int i = 0; i < maxIterations; i++)
	{
		setAnts();
		moveAnts();
		updateTrails();
		updateBestSolution();
		if (i % 20 == 0) {
			cout << "Iteration: " << i << endl;
			cout << "Length of the best path founded: " << bestTourLength << endl;
			cout << "Order of best solution: ";
			/*for (int i = 0; i < numberOfCities; i++)
			{
				cout << bestTourOrder[i] << "-->";
			}*/
			cout << endl;
		}
	}
	cout <<"LMin " << Lmin << endl;
	return bestTourOrder;
}

void AntColony::setStartTrails()
{
	for (int i = 0; i < numberOfCities; i++)
	{
		for (int j = 0; j < numberOfCities; j++)
		{
			if (i == j) trails[i][j] = 0;
			else {
				trails[i][j] = 0.2; //start number of feromon
			}
		}
	}
}

void AntColony::setSightMatrix()
{
	for (int i = 0; i < numberOfCities; i++)
	{
		for (int j = 0; j < numberOfCities; j++)
		{
			if (i != j) {
				sightMatrix[i][j] = 1 / graph[i][j];
			}
			else {
				sightMatrix[i][j] = 0;
			}
		}
	}
}

void AntColony::moveAnts()
{
	for (int i=currentIndex; i < numberOfCities-1; i++, currentIndex++)
	{
		for(auto ant: ants)
		{
				ant.visitCity(i, selectCity(ant));
		}
	}
}

int AntColony::selectCity(Ant ant) {
	float random = static_cast <float>(rand()%1000)/static_cast<float>(1000);
	if (random < randomFactor) {
		for (int i = 0; i < numberOfCities; i++)
		{
			if (!ant.isVisited(i)) {
				return i;
			}
		}
	}
	calculateProbabilities(ant);
	float counter = 0;
	int index = 0;
	for (int i = 0; i < numberOfCities; i++)
	{
		counter += probabilities[i];
		if (counter >= random) {
			index= i;
			break;
		}
	}
	return index;
}

void AntColony::calculateProbabilities(Ant ant)
{
	int i = ant.trail[currentIndex];
	double feromone = 0.0;
	for (int j = 0; j < numberOfCities; j++)
	{
		if (!ant.isVisited(j)) {
			feromone += pow(trails[i][j], alpha) * pow(sightMatrix[i][j], beta);
		}
	}
	for (int j = 0; j < numberOfCities; j++)
	{
		if (ant.isVisited(j)) {
			probabilities[j] = 0;
		}
		else {
			double current = pow(trails[i][j], alpha) * pow(sightMatrix[i][j], beta);
			probabilities[j] = current / feromone;
		}
	}
}

void AntColony::updateTrails()
{
	for (int i = 0; i < numberOfCities; i++)
	{
		for (int j = 0; j < numberOfCities; j++)
		{
			trails[i][j] *= (1 - evaporation); //feromon disappear
		}
	}
	for (auto ant : ants) {
		float contribution = (Lmin / ant.trailLength(graph));
		for (int i = 0; i < numberOfCities - 1; i++) {
			trails[ant.trail[i]][ant.trail[i + 1]] += contribution;
		}
		trails[ant.trail[numberOfCities - 1]][ant.trail[0]] += contribution;
	}
}

void AntColony::updateBestSolution()
{
	if (bestTourOrder[0]==0 && bestTourOrder[1]==0) {
		bestTourOrder = ants[0].trail;
		bestTourLength = ants[0].trailLength(graph);
	}
	for (auto ant : ants) {
		if (ant.trailLength(graph) < bestTourLength) {
			bestTourLength = ant.trailLength(graph);
			bestTourOrder = ant.trail;
		}
	}
}

void AntColony::getLMin()
{
	int Lmin = 0;
	vector<int> checked;
	int i = 0;
	while (checked.size() < numberOfCities)
	{
		if (checked.size() + 1 == numberOfCities)
		{
			Lmin += graph[i][0];
			break;
		}
		int min = 51;
		int count = 0;
		checked.push_back(i);
		for (int j = 0; j < numberOfCities; j++)
		{
			if (min > graph[i][j] && CheckInChecked(j, checked))
			{
				min = graph[i][j];
				count = j;
			}
		}
		i = count;
		Lmin += min;
	}
	this->Lmin = Lmin;
}

bool AntColony::CheckInChecked(int a, vector<int> checked)
{
	for (int n = 0; n < checked.size(); n++)
	{
		if (a == checked[n])
		{
			return false;
		}
	}
	return true;
}