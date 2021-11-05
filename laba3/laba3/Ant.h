#pragma once
class Ant
{
public:
	int trailSize;
	int* trail;
	bool* visited;

	Ant(int tourLength);
	void visitCity(int currentIndex, int city);
	bool isVisited(int i);
	void forget();
	float trailLength(float** graph);
};

