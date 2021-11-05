#include "Ant.h"

Ant::Ant(int tourLength)
{
	trailSize = tourLength;
	trail = new int[tourLength];
	visited = new bool[tourLength];
}

void Ant::visitCity(int currentIndex, int city)
{
	trail[currentIndex + 1] = city;
	visited[city] = true;
}

bool Ant::isVisited(int i)
{
	return visited[i];
}

void Ant::forget() {
	for (int i = 0; i < trailSize; i++) {
		visited[i] = false;
	}
}

float Ant::trailLength(float** graph)
{
	float length = graph[trail[trailSize - 1]][trail[0]];
	for (int i = 0; i < trailSize - 1; i++)
	{
		length += graph[trail[i]][trail[i + 1]];
	}
	return length;
}
