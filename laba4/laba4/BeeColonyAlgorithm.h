#pragma once
#include <vector>
#include "Item.h"
#include "Bagpack.h"
#include <set>
class BeeColonyAlgorithm
{
	int number_of_scouts = 24, 
		number_random_scouts = 8,
		number_best_scouts = number_of_scouts - number_random_scouts,
		number_iter = 100,
		number_plots = 100,
		number_items = 100,
		n_foragers = 15;

	vector<vector<bool>> plots;
	vector<int> prices;

	vector<bool> isTaken;
	Bagpack bagpack;

	int best_solution_price=0,
		best_solution_weight=0;
	vector<bool> best_solution;


	void sortPlotsByPrice();
public:
	BeeColonyAlgorithm(int);
	void solve();
};

